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
    .option('plugins', {
        describe: 'The path for plugins.json',
        default: 'app/plugins.json'
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

// These packages always need to be initialized
const fs = require('fs');
const restify = require('restify');
const bunyan = require('bunyan');
const tree = require('inexor-tree');

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

// Mother inexor
inexor = {};

// Create a web server
inexor.server = restify.createServer({
    name: 'Inexor',
    log: log,
    version: '0.0.9'
});

// Create the tree
inexor.tree = tree.Root.createTree(inexor.server);
inexor.tree.grpc.connect();

// Extend logger using the plugin.
inexor.server.pre(restify.pre.sanitizePath());
inexor.server.use(restify.requestLogger());
inexor.server.use(function(request, response, next) {
    request.log.info('%s -- %s %s %s', request.connection.remoteAddress, request.method, request.url, request.headers['user-agent']);
    next();
});

//TODO: This is just a draft, introduce a way to register GET/SETTERS for the REST interface
inexor.server.use(restify.bodyParser()); // for parsing application/json

// Serve static files from the assets folder
inexor.server.get(/^\/?.*/, restify.serveStatic({
    directory: __dirname + './../public',
    default: 'index.html'
}));

inexor.tree.on('ready', function() {
  inexor.server.log.info('Inexor Tree initialized');

  let plugins = JSON.parse(fs.readFileSync(argv.plugins));
  require('plugins.js')(plugins, inexor).then(function(msg) {
    inexor.server.log.info(msg);
    // Finally start the server
    inexor.server.listen(argv.port, argv.host, function () {
        // inexor.status = 'ready'; // TODO: THIS IS FOR CEF_INITIALIZATION AND CURRENTLY NOT USED
        inexor.server.log.info('Inexor-Node-RPC listening on %s:%s', argv.host, argv.port);
    });
  }).catch(function(err) {
    inexor.server.log.err(err);
  })
})

// Load controllers
// TODO: Add a standardized way to load Controllers
// var EditorSettings = require('./controllers').EditorSettings;
// inexor.editorSettings = new EditorSettings(inexor.tree, server);
