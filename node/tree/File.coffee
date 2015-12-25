fs = require 'fs'
Promise = require 'promise'

Node = require './Node'

class File extends Node
	constructor: (@path) ->
	
	# @return {Promise}
	read: () ->
		return Promise.denodeify(fs.readFile)(@path, 'utf8')
		
	write: (data, flag = 'w') ->
		return Promise.denodeify(fs.writeFile)(@path, data, { flag: flag })

	resolve: (path) ->
		# check if a path is valid and it's content is a directory
		@resolve(path, __dirname)
			.then(absolutePath) ->
				Promise.denodeify(fs.lstat)(absolutePath)
					.then(stat)
			      			if stat.isFile()
			       				return absolutePath 
	
module.exports = File		
