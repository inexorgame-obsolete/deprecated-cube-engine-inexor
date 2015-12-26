
# A base function which returns an ECMA6/Proxy
# This mirrors an instance of a given object as a non-op proxy

link = (obj) ->
	return new Proxy(obj, {})

module.exports = link
