#!/usr/bin/env node
var argv = require('yargs')
    .usage('Usage: $0 <command> [options]')
    .example('$0 -p 3000', 'Starts the Inexor RPC at port 3000')
    .option('p', {
        alias: 'port',
        describe: 'Specify the server port',
        default: 48702
    })
    .option('h', {
        alias: 'host',
        describe: 'The host to listen on',
        default: 'localhost'
    })
    .option('l', {
        alias: 'logfile',
        describe: 'Server`s log file',
        default: 'server.log'
    })
    .option('level', {
        describe: 'The standard log level',
        default: 'info'
    })
    .option('v', {
        alias: 'verbose',
        describe: 'Should the server log verbose',
        default: false
    })
    .config('config', function (configPath) {
        // This can (exceptionally) be synchronous since we don't really want to anything
        // before the configuration has been passed
        return JSON.parse(fs.readFileSync(configPath, 'utf-8'))
    })
    .alias('c', 'config')
    .help('h')
    .alias('h', 'help')
    .epilog('copyright 2016')
    .argv;

const grpc = require('grpc');
var restify = require('restify');
var bunyan = require('bunyan');

// Self-framework
var createTree = require('./tree').Root.createTree;

streams = [{
    level: argv.level,
    path: argv.logfile
}]

// Additionally push a command-line stream log with level debug when verbosity is enabled
if (argv.verbose) {
     streams.push({
         level: 'debug',
         stream: process.stdout
     });
}

var log = bunyan.createLogger({
    name: 'Inexor',
    streams: streams
});

// Create a server
var server = restify.createServer({
    name: 'Inexor',
    log: log,
    version: '0.0.8'
});

//Create the inexor tree
inexor = {};
inexor.tree = createTree(server, grpc)

var EditorSettings = require('./controllers').EditorSettings;
inexor.editorSettings = new EditorSettings(inexor.tree, server);

//Extend logger using the plugin.
server.use(restify.requestLogger());

// Sanitize path
server.pre(restify.pre.sanitizePath());

// Use nginx-alike logging style: address, method, url, user-agent
server.use(function(request, response, next) {
    request.log.info('%s -- %s %s %s', request.connection.remoteAddress, request.method, request.url, request.headers['user-agent']);
    next();
});

server.use(restify.bodyParser()); // for parsing application/json

/**
 * @tutorial REST-tutorial
 * The IPC Server offers a RESTfull approach to talk to it's C++ backend
 * To communicate with the server use `GET` and `POST` requests respectively.
 * Currently the server uses `text/plain` requests for interaction, which might change in the future.
 * Following methods are currently offered by the API
 * 
 * - `tree/dump` will dump the hierarchical structure of the tree
 * - send a `GET` request to `tree/member` to get a `text/plain` representation of the object
 * - send a `POST` request with `text/plain` in `BODY` to `tree/member` to synchronize specified member (returns either `200` or a failure excerpt)
 */
inexor.tree.rest = {
        "get": function(request, response, next) {
        	try {
                let node = inexor.tree.findNode("/" + request.params[0]);
                if (node.isContainer) {
                    response.send(200, node.toString());
                } else {
                    response.send(200, node.get());
                }
        	} catch (e) {
        		server.log.error(e);
        	}
            return next();
        },

        "post": function(request, response, next) {
           	try {
                let node = inexor.tree.findNode("/" + request.context[0]);
                node.set(request.body);
                response.send(200);
        	} catch (e) {
        		server.log.error(e);
        	}
            return next();
        },

        "delete": function(request, response, next) {
           	try {
                let node = inexor.tree.findNode("/" + request.context[0]);
                let parentNode = node.getParent();
                parentNode.removeChild(node._name);
                response.send(200);
        	} catch (e) {
        		server.log.error(e);
        	}
            return next();
        },

        "dump": function(request, response, next) {
           	try {
                response.send(inexor.tree.toString());
        	} catch (e) {
        		server.log.error(e);
        	}
            return next();
        }
};

// REST API for the inexor tree
server.get("/tree/dump", inexor.tree.rest.dump);
server.get(/^\/tree\/(.*)/, inexor.tree.rest.get);
server.post(/^\/tree\/(.*)/, inexor.tree.rest.post);

// Serve static files from the assets folder
server.get(/^\/?.*/, restify.serveStatic({
    directory: __dirname + './../public',
    default: 'index.html'
}));

//Listen on server
server.listen(argv.port, argv.host, function () {
    server.log.info('Inexor-Node-RPC listening on %s:%s', argv.host, argv.port);
});
