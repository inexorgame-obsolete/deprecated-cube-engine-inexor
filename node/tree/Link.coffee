
# A base class which can keep the reference of a 
class Link extends Proxy
	# Mirror access to the object using ECMA proxies 
	constructur: (target, handler) ->
		super
