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
        default: '/tmp/server.log'
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
    .epilog('copyright 2015')
    .argv;

var express = require('express');
var serveStatic = require('serve-static');
var bodyParser = require('body-parser');
var bunyan = require('bunyan');

// Application level dependencies
var app = express();
var EvalCubescript = require('./rpc.js');

streams = [
    {
        level: argv.level,
        path: argv.logfile
    }
]
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


// This logs all requests with bunyan
// Use nginx-alike logging style: address, method, url, user-agent
app.use(function(req, res, next) {
   log.info('%s -- %s %s %s', req.ip, req.method, req.originalUrl, req.headers['user-agent']);
   next();
});

app.use(bodyParser.json()); // for parsing application/json

//Send POST-only requests to /execute
//TODO: Sanitize data and restrict access to localhost-only!
//TODO: Resolve promises and send single-request / talk with Hanack about this
app.post('/execute', function(req, res, next) {
    stack = []
    for (var key in req.body) {
        stack.push(EvalCubescript(req.body[key]));
    }
    res.json(stack);
    next();
});

// Serve static files from the assets folder
app.use(serveStatic('assets', {'index': ['inexorui/index.html']}));

// Handle errors
app.use(function(err, req, res, next) {
    log.error('%s %s %s', req.method, req.originalUrl, err.stack);
    next();
});

app.listen(argv.port, argv.host, function () {
  log.info('Inexor-Node-RPC listening on %s:%s', argv.host, argv.port);
});
