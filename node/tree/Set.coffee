Promise = require 'promise'
Link = require './Link.coffee'

# Extend ECMA6/Map since it does almost exactly what we want

class Set extends Map
	set: (key, value) ->
		return Promise.denodeify(super)(key, value)
		
	get: (key) ->
		return new Link(super(key))
	