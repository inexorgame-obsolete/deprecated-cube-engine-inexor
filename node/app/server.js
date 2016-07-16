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

//Create a server
var server = restify.createServer({
    name: 'Inexor',
    log: log,
    version: '0.0.9'
});

//Extend logger using the plugin.
server.use(restify.requestLogger());

// Sanitize path
server.pre(restify.pre.sanitizePath());

// Use nginx-alike logging style: address, method, url, user-agent
server.use(function(request, response, next) {
    request.log.info('%s -- %s %s %s', request.connection.remoteAddress, request.method, request.url, request.headers['user-agent']);
    next();
});

//TODO: This is just a draft, introduce a way to register GET/SETTERS for the REST interface
server.use(restify.bodyParser()); // for parsing application/json

//Normally the App/Middleware object of Express/Restify
//We manually assign the Tree which is ALWAYS needed
inexor = {};
inexor.tree = tree.Root.createTree(server);

//Load plugins.json -> require every plugin and assign a namespace
var plugins = JSON.parse(fs.readFileSync(argv.plugins));

const PLUGIN_FOLDER = 'plugins';
const RESERVED_PLUGINS = ['rest']; // These can only be registered from app/plugins/ folder

//Depending wether plugins-xy or inexor-plugins-xy is used, it is loaded from either app/plugins or NPM

plugins.forEach(function(pluginName) {
    let names = pluginName.split('-');
    let name = names[names.length -1]; // The last element
    let path = '';
    
    if (names[0] == 'inexor') {
        if (RESERVED_PLUGINS.includes(name)) return; // This should jump directly to the next forEach element?
        path = pluginName;
    } else {
        path = './plugins/' + name;
    }
    
    // Read the meta data from package
    let pluginMeta = require(path + '/package.json');
    let plugin = require(path)(tree, server);
    // let sync = (typeof(pluginMeta.plugin.sync) === 'boolean') ? pluginMeta.plugin.sync : false; // Set default to false
    
    // inexor.tree.addChild(name, 'node', plugin, sync, false);
    inexor.tree[name] = plugin;
        
    if (pluginMeta.plugin.hasOwnProperty('routes')) {
        for (routeType in pluginMeta.plugin.routes) {
            for (route in pluginMeta.plugin.routes[routeType]) {
                // TODO: This is not generic and needs improvement..
                
                let func = pluginMeta.plugin.routes[routeType][route]; // Function name
                
                switch (routeType) {
                case 'get':
                    server.get(route, inexor.tree[name][func]);
                    break;
                case 'set':
                    server.post(route, inexor.tree[name][func]);
                    break;
                }
            }
        }
    }
});

//REST API for the inexor tree
server.get('/tree/dump', inexor.tree.rest.dump);
server.get(/^\/tree\/(.*)/, inexor.tree.rest.get);
server.post(/^\/tree\/(.*)/, inexor.tree.rest.post);

// Load controllers
// TODO: Add a standardized way to load Controllers
// var EditorSettings = require('./controllers').EditorSettings;
// inexor.editorSettings = new EditorSettings(inexor.tree, server);

// Serve static files from the assets folder
server.get(/^\/?.*/, restify.serveStatic({
    directory: __dirname + './../public',
    default: 'index.html'
}));

//Listen on server
server.listen(argv.port, argv.host, function () {
    // inexor.status = 'ready'; // TODO: THIS IS FOR CEF_INITIALIZATION AND CURRENTLY NOT USED
    server.log.info('Inexor-Node-RPC listening on %s:%s', argv.host, argv.port);
});
