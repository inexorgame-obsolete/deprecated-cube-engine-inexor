Promise = require 'promise'
restify = require 'restify'
bunyan = require 'bunyan'
fs = require 'fs'

argv = require('yargs')
	.option( 'h', {
		alias: 'host',
		demand: 'false',
		default: 'localhost',
		describe: 'Which host to listen on',
		type: 'string'
	} )
	.option( 'p', {
		alias: 'port',
		demand: 'false',
		default: '48702',
		describe: 'The server port to be used',
		type: 'string'
	} )
	.option( 't', {
		alias: 'tree',
		demand: 'true',
		default: '../bin/tree.proto',
		describe: 'The Inexor tree file',
		type: 'string'
	} )
	.option( 'c', {
		alias: 'config',
		demand: 'false',
		default: 'config.json',
		describe: 'The config file for the server',
		type: 'string'
	} )
	.option( 'v', {
		alias: 'verbose',
		demand: 'false',
		default: false,
		describe: 'Log into the command line',
		type: 'boolean'
	} )
	.argv

defaultSettings = {
	name: 'Inexor',
	version: '0.1.0',
	level: 'debug',
	logFile: 'server.log'
}
	
# Build a NodeTree

Promise.denodeify(fs.readFile)(argv.c, 'utf8')
	.then(JSON.parse)
	.then (settings) ->
		# Merge defaultSettings with the configuration file
		settings[key] = val for key, val of defaultSettings when not settings[key]?
		
		streams = [
			{
				level: settings.level,
				path: settings.logFile
			}
		]
		
		if argv.v is true
			streams.push( {
				level: 'debug',
				stream: process.stdout
			})
		
		# Create a logging interface
		# Optionally add a command-line stream with loglevel, configurable through the command line	
		log = bunyan.createLogger(
			name: settings.name,
			streams: streams
		)
		
		# Dynamically create settings for restify
		server = restify.createServer({ name: settings.name, version: settings.version, log: log})
		
		# Bind on specified port
		server.listen argv.p, argv.h, ->
			server.log.info '%s listening at %s', server.name, server.url

		# Routing. Always preffer the tree over the modules
