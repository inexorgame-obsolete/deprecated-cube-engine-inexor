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
	
module.exports = File		
