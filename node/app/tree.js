/** Inexor Tree **/

var separator = "/";

var isValidDatatype = function(datatype) {
	// var valid = datatype == "node" || datatype == "string" || datatype == "integer" || datatype == "float" || datatype == "bool" || datatype == "timestamp";
	// console.log("Datatype: " + datatype + ": " + valid);
	return datatype == "node" || datatype == "string" || datatype == "integer" || datatype == "float" || datatype == "bool" || datatype == "timestamp";
};

var isValidName = /^[\w ]+$/;

var TreeNode = function(parent, name, datatype, initialValue = null, sync = false, readOnly = false) {

	/**
	 * The parent node or null if the node is the root node.
	 */
	this._parent = parent;

	/**
	 * The name of the tree node.
	 * Not unique!
	 */
	this._name = name;

	/**
	 * The path of the tree node.
	 * Unique!
	 */
	if (parent != null) {
		if (parent._path != separator) {
			this._path = parent._path + separator + name;
		} else {
			this._path = separator + name;
		}
	} else {
		this._path = separator;
	}
	
	/**
	 * The datatype of the tree node.
	 */
	if (isValidDatatype(datatype)) {
		this._datatype = datatype;
	} else {
		console.log("Not a valid datatype!");
		throw "Datatype not valid";
	}

	/**
	 * State if the tree node is read only.
	 */
	this._readOnly = readOnly;


	if (datatype == "node") {
		
		// Container

		this.isContainer = true;
		this.isLeaf = false;

		/**
		 * Initializes the map of child nodes.
		 */
		this._value = new Map();

	} else {
		
		// Leaf

		this.isContainer = false;
		this.isLeaf = true;

		/**
		 * Sets the initial value.
		 */
		if (initialValue != null) {
			this._value = initialValue;
		} else {
			console.log("No initial value provided!");
			throw "No initial value provided";
		}

		/**
		 * Sets if the tree node should be synchronized.
		 */
		this._sync = sync;

		/**
		 * The listeners which are called before changing the value of the tree node.
		 */
		this._preSetListeners = new Map();

		/**
		 * The listeners which are called after changing the value of the tree node.
		 */
		this._postSetListeners = new Map();

		/**
		 * The listeners which are called after node synchronization.
		 */
		this._postSyncListeners = new Map();

	}

	/**
	 * Returns the path of the tree node.
	 */
	this.getPath = function() {
		return this._path;
	};

	/**
	 * Returns either the value or the child nodes.
	 */
	this.get = function() {
		return this._value;
	};

	/**
	 * Sets the value of the tree node.
	 */
	this.set = function(newValue, preventSync = false) {
		if (this.isLeaf && !this._readOnly) {

			var oldValue = this._value;

			// Call pre set listeners
			// Pre set listeners can interrupt setting the value
			for (var [listenerName, listenerCallback] of this._preSetListeners.entries()) {
				if (!listenerCallback(this, oldValue, newValue)) {
					return;
				}
			}

			// Set the value
			this._value = newValue;
			
			// Set the timestamp when the value was last changed
			this._timestamp = Date.now();

			// Call post set listeners
			for (var [listenerName, listenerCallback] of this._postSetListeners.entries()) {
				listenerCallback(this, oldValue, newValue);
			}

			if (this._sync && !preventSync) {

				try {
					// Do synchronization
					var message = {};
					// TODO: this._name is wrong
					message[this._name] = newValue;
					console.log(message);
					inexor.tree.grpc.synchronize.write(message);

					// Call post sync listeners
					for (var [listenerName, listenerCallback] of this._postSyncListeners.entries()) {
						listenerCallback(this, oldValue, newValue);
					}
				} catch(err) {
					
				}

			}
		}
	};

	/**
	 * Returns true if a child node exists with the given name.
	 */
	this.hasChild = function(name) {
		return this.isContainer && this._value.has(name);
	};

	/**
	 * Returns the child with the given name.
	 */
	this.getChild = function(name) {
		if (this.hasChild(name)) {
			return this._value.get(name);
		}
	};

	/**
	 * Returns the child names.
	 */
	this.getChildNames = function() {
		if (this.isContainer) {
			var childNames = [];
			for (var key of this._value.keys()) {
				childNames.push(key);
			}
			return childNames;
		} else {
			return [];
		}
	};

	/**
	 * Adds a child.
	 * @param name Must not contain whitespace or dots
	 * @param datatype One of "string", "integer"
	 */
	this.addChild = function(name, datatype, initialValue = null, sync = false, readOnly = false) {
		if (this.hasChild(name)) {
			return this.getChild(name);
		} else if (this.isContainer && isValidName.test(name) && isValidDatatype(datatype)) {
			
			// Create the child tree node
			var childTreeNode = new TreeNode(this, name, datatype, initialValue, sync, readOnly);
			
			// Add the child tree node to the children map
			this._value.set(name, childTreeNode);

			// Define getters and setters , so we can use object notation:
			//
			// Getter:
			//   var value = inexor.tree.path.to.the.node;
			// Setter:
			//   inexor.tree.path.to.the.node = value;
			var self = this;
			Object.defineProperty(self, name, {
				get: function() {
					// var child = self.getChild(name);
					if (childTreeNode.isContainer) {
						return childTreeNode;
					} else {
						return childTreeNode.get();
					}
				},
				set: function(newValue) {
					// var child = self.getChild(name);
					childTreeNode.set(newValue);
				}
			});
			
			return childTreeNode;
		} else {
			console.log("Failed to create child node: " + name + " (" + datatype + ")");
			throw "Failed to create child node";
		}
	};

	/**
	 * Shortcut for addChild(name, "node");
	 */
	this.addNode = function(name) {
		return this.addChild(name, "node");
	};

	/**
	 * Removes a child by name.
	 */
	this.removeChild = function(name) {
		if (this.hasChild(name) && !this.getChild(name)._readOnly) {
			this._value.delete(name);
		}
	};

	/**
	 * Returns the parent node or null if the tree node is the root node.
	 */
	this.getParent = function() {
		if (this._path != separator) {
			return this._parent;
		} else {
			return null;
		}
	};

	/**
	 * Registers a listener which is called before changing the value of the tree node.
	 */
	this.addPreSetListener = function(name, callback) {
		if (this.isLeaf) {
			this._preSetListeners.set(name, callback);
		}
	};

	/**
	 * Registers a listener which is called after changing the value of the tree node.
	 */
	this.addPostSetListener = function(name, callback) {
		this._postSetListeners.set(name, callback);
	};

	/**
	 * Registers a listener which is called after node synchronization.
	 */
	this.addPostSyncListener = function(name, callback) {
		this._postSyncListeners.set(name, callback);
	};

	/**
	 * Removes a pre set listener.
	 */
	this.removePreSetListener = function(name) {
		this._preSetListeners.delete(name);
	};

	/**
	 * Removes a post set listener.
	 */
	this.removePostSetListener = function(name) {
		this._postSetListeners.delete(name);
	};

	/**
	 * Removes a post sync listener.
	 */
	this.removePostSyncListener = function(name) {
		this._postSyncListeners.delete(name);
	};

	/**
	 * Returns a json representation.
	 */
	this.toJson = function() {
		if (this.isContainer) {
			var json = {};
			for (var [name, childNode] of this._value.entries()) {
				json[name] = childNode.toJson();
			}
			return json;
		} else {
			return this._value;
		}
	};

	// TODO: import von 
};

/**
 * Creation method for the inexor tree. The root node of the tree additionally
 * has a findNode(path) method and a REST API.
 */
var Tree = function(server, grpc) {

	/**
	 * Creates the root node of the tree
	 */
	var root = new TreeNode(null, "", "node");

	/**
	 * Find nodes by by path!
	 * @param path The path of the node.
	 * @return The node (not the value).
	 */
	root.findNode = function(path) {
		var splittedPath = path.split(separator);
		var node = root;
		for (var i = 1; i < splittedPath.length; i++) {
			node = node.getChild(splittedPath[i]);
		}
		return node;
	};

	root.createRecursive = function(path, datatype, initialValue = null, sync = false, readOnly = false) {
		var splittedPath = path.split(separator);
		var node = root;
		for (var i = 1; i < splittedPath.length - 1; i++) {
			if (!node.hasChild(splittedPath[i])) {
				node = node.addChild(splittedPath[i], "node");
			} else {
				node = node.getChild(splittedPath[i]);
			}
		}
		if (!node.hasChild(splittedPath[splittedPath.length - 1])) {
			node = node.addChild(splittedPath[splittedPath.length - 1], datatype, initialValue, sync, readOnly);
		} else {
			node = node.getChild(splittedPath[splittedPath.length - 1]);
		}
		return node;
	};

	/**
	 * Generic REST API for the inexor tree.
	 */
	root.rest = {

		"get": function(request, response, next) {
			
			response.send(200, root.findNode("/" + request.params[0]).get());
			return next();
		},

		"post": function(request, response, next) {
			var node = root.findNode("/" + request.context[0]);
			node.set(request.params);
			response.send(200);
			return next();
		},

		"delete": function(request, response, next) {
			var node = root.findNode("/" + request.context[0]);
			var parentNode = node.getParent();
			parentNode.removeChild(node._name);
			response.send(200);
			return next();
		},

		"dump": function(request, response, next) {
			response.send(root.toJson());
		}

	};

	root.grpc = {};
	
	// Load the proto definition
	root.grpc.protoDescriptor = grpc.load(__dirname + "/../../inexor/rpc/inexor_service.proto");
	// console.log(root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName["fullscreen"].options["(path)"]);

	/**
	 * Returns the path of the field key.
	 */
	root.grpc.getPath = function(key) {
		return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[key].options["(path)"];
	};

	/**
	 * Returns the datatype of the field key.
	 */
	root.grpc.getDatatype = function(key) {
		return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[key].type.name;
	};

	/**
	 * Returns the id of the field key.
	 */
	root.grpc.getId = function(key) {
		return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[key].id;
	};

	/**
	 * Loads the field names from .proto and initializes the tree recursively.
	 */
	root.grpc.initializeTree = function() {
		for (var key in root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName) {
			try {
				root.createRecursive(root.grpc.getPath(key), root.grpc.getDatatype(key), false, true, false);
			} catch (err) {}
		}
	};

	/**
	 * Connects the the server and initializes the tree.
	 */
	root.grpc.connect = function() {

		root.grpc.treeServiceClient = new root.grpc.protoDescriptor.inexor.tree.TreeService("localhost:50051", grpc.credentials.createInsecure());

		root.grpc.synchronize = root.grpc.treeServiceClient.synchronize();

		root.grpc.synchronize.on("data", function(message) {
			// console.log(message);
			var key = message.key;
			var value = message[key];
			var path = root.grpc.getPath(key);
			var node = root.findNode(path);
			console.log(key + " (" + path + ") = " + value);
			node.set(value, true);
		});

		root.grpc.synchronize.on("end", function() {
			// The server has finished sending
			console.log("inexor.tree.grpc.synchronize.end");
			// TODO: here we could stop the Inexor Flex because Inexor Core is gone!
		});

		root.grpc.synchronize.on("status", function(status) {
			// process status
			console.log("inexor.tree.grpc.synchronize.status: " + status);
		});
		
		root.grpc.initializeTree();

	};
	
	root.grpc.connect();
	
	// TODO: disconnect grpc

	return root;
};

module.exports = Tree;
