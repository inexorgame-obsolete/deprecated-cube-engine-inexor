
# A base class which can keep the reference of a 
class Link
	constructor: (obj) ->
		this.obj = new Proxy(obj, {])

	# Mirror access to the object using ECMA proxies 
