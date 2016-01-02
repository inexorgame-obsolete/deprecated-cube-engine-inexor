fs = require 'fs'
Promise = require 'promise'

# Define an abstract base class Node
class Node
	construct: (@tree) ->

	# a basic abstract function to resolve the absolute path given either the tree
	# directory or the current working directory as a search path
	resolve: (path, dir) ->
		return Promise.denodeify(fs.realpath)(path, {@tree, dir})

module.exports = Node
