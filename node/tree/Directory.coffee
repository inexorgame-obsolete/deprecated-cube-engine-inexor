fs = require 'fs'
Promise = require 'promise'

Node = require './Node'

# Directory base class
class Directory extends Node
	constructor: (@path) ->
	
	# Returns a list of underlaying files
	# @return {Promise}
	ls: () ->
		return Promise.denodeify(fs.readdir)(@path)
	
	# Returns the absolute path. 
	# When throwing a non-directory it will set the promise to failed
	# @return string
	resolve: (path) ->
		# check if a path is valid and it's content is a directory
		@resolve(path, __dirname)
			.then(absolutePath) ->
				Promise.denodeify(fs.lstat)(absolutePath)
					.then(stat)
			      			if stat.isDirectory()
			       				return absolutePath 

module.exports = Directory
