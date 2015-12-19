Promise = require 'promise'
restify = require 'restify'
bunyan = require 'bunyan'
fs = require 'fs'

defaultSettings = {
	name: "Inexor",
	version: "0.1.0",
	level: "debug",
	logFile: "server.log"
}

# Import all modules from /modules
# modules = require '/modules/
	
# Build a NodeTree

Promise.denodeify(fs.readFile)('config.json', 'utf8')
	.then(JSON.parse)
	.then (settings) ->
		# Merge defaultSettings with the configuration file
		settings[key] = val for key, val of defaultSettings when not settings[key]?
		
		#for key in Object.keys(defaultSettings)
		#	do (key) ->
		#		if !(key of settings)
		#			settings[key] = defaultSettings[key]
		
		# Create a logging interface
		# Optionally add a command-line stream with loglevel, configurable through the command line	
		log = bunyan.createLogger(
			name: settings.name,
			streams:[
				level: settings.level,
				path: settings.logFile
			]
		)
		settings.log = log
		
		# Dynamically create settings for restify
		
		server = restify.createServer({ name: settings.name, version: settings.version, log: settings.log})
		
		# Bind on specified port
		server.listen 8080, ->
			server.log.info '%s listening at %s', server.name, server.url

		# Routing. Always preffer the tree over the modules
