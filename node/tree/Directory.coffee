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
		# check if a path is a valid directory
		# additionally resolve a relative path, if needed
		
		return Promise.denodeify(fs.realpath)(path)
			.then (value) ->
				Promise.denodeify(fs.lstat)(path)
					.then (stat) ->
						if stat.isDirectory()
							return value

module.exports = Directory
