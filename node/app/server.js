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

var restify = require('restify');
var bunyan = require('bunyan');

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

var server = restify.createServer({
    name: 'Inexor',
    log: log,
    version: '0.0.6'
});

//Extend logger using the plugin.
server.use(restify.requestLogger());

// Use nginx-alike logging style: address, method, url, user-agent
server.use(function(req, res, next) {
    req.log.info('%s -- %s %s %s', req.connection.remoteAddress, req.method, req.url, req.headers['user-agent']);
    next();
});

server.use(restify.bodyParser()); // for parsing application/json

// Serve static files from the assets folder
server.get(/.*/, restify.serveStatic({
    directory: 'public',
    default: 'index.html'
 }));

server.listen(argv.port, argv.host, function () {
    server.log.info('Inexor-Node-RPC listening on %s:%s', argv.host, argv.port);
});
