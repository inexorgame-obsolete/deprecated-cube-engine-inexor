const util = require("./util");
var Node = require("./Node");

/**
 * Represents the inexor root tree
 * @name Root
 */
class Root extends Node {
    /**
     * @constructor
     * @see Node.constructor
     */
    constructor() {
        // Initialise this as the root node
        super(null, "", "node");
        
        /**
         * Generic REST API for the inexor tree.
         * @TODO: Such functionality should be outsourced?
         */
        this.rest = {
                "get": function(request, response, next) {
                    let node = this.findNode("/" + request.params[0]);
                    if (node.isContainer) {
                        response.send(200, node.toString());
                    } else {
                        response.send(200, node.get());
                    }
                    return next();
                },

                "post": function(request, response, next) {
                    let node = root.findNode("/" + request.context[0]);
                    node.set(request.params);
                    response.send(200);
                    return next();
                },

                "delete": function(request, response, next) {
                    let node = this.findNode("/" + request.context[0]);
                    let parentNode = node.getParent();
                    parentNode.removeChild(node._name);
                    response.send(200);
                    return next();
                },

                "dump": function(request, response, next) {
                    response.send(this.toString());
                }
        };
    }
    
    /**
     * @function
     * @name Root.findNode
     * @param {string} path
     * @return {Node}
     */
    findNode(path) {
        let splittedPath = path.split(util.seperator);
        let node = this;
        for (var i = 1; i < splittedPath.length; i++) {
            node = node.getChild(splittedPath[i]);
        }
        
        return node;
        // TODO: Use a binary-tree-search-approach?
        // TODO: DAFUQ, IS THIS TESTED? :D
    }
    
    /**
     * @function
     * @name Root.createRecursive
     * @param {string} path
     * @param {datatype} datatype
     * @param {mixed} initialValue
     * @param {bool} sync
     * @param {bool} readOnly
     * @param {int} protoKey
     */
    createRecursive(path, datatype, initialValue = null, sync = false, readOnly = false, protoKey = null) {
        let splittedPath = path.split(util.separator);
        let node = root;
        for (var i = 1; i < splittedPath.length - 1; i++) {
            if (!node.hasChild(splittedPath[i])) {
                node = node.addChild(splittedPath[i], "node");
            } else {
                node = node.getChild(splittedPath[i]);
            }
        }
        if (!node.hasChild(splittedPath[splittedPath.length - 1])) {
            node = node.addChild(splittedPath[splittedPath.length - 1], datatype, initialValue, sync, readOnly, protoKey);
        } else {
            node = node.getChild(splittedPath[splittedPath.length - 1]);
        }
        return node;
    }
}

/**
 * Created an Inexor Root Tree
 * @function
 * @name 
 * @param server
 * @param grpc
 * @returns {Root}
 */
function createTree(server, grpc) {
    let root = new Root();
    
    root.grpc = {};
    
    // Load the proto definition
    root.grpc.protoDescriptor = grpc.load(__dirname + "/../../inexor/rpc/treedata.gen.proto");
    // console.log(root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName["fullscreen"].options["(path)"]);

    /**
     * Returns the path of the field by proto key.
     */
    root.grpc.getPath = function(protoKey) {
        return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[protoKey].options["(path)"];
    };

    /**
     * Returns the datatype of the field by proto key.
     */
    root.grpc.getDatatype = function(protoKey) {
        return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[protoKey].type.name;
    };

    /**
     * Returns the id of the field by proto key.
     */
    root.grpc.getId = function(protoKey) {
        return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[protoKey].id;
    };

    /**
     * Loads the field names from .proto and initializes the tree recursively.
     */
    root.grpc.initializeTree = function() {
        for (var protoKey in root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName) {
            try {
                root.createRecursive(root.grpc.getPath(protoKey), root.grpc.getDatatype(protoKey), false, true, false, protoKey);
            } catch (err) {
                console.log(err);
            }
        }
    };

    /**
     * Connects the the server and initializes the tree.
     */
    root.grpc.connect = function() {

        root.grpc.treeServiceClient = new root.grpc.protoDescriptor.inexor.tree.TreeService("localhost:50051", grpc.credentials.createInsecure());

        root.grpc.synchronize = root.grpc.treeServiceClient.synchronize();

        root.grpc.synchronize.on("data", function(message) {
            console.log(message.key);
            var protoKey = message.key;
            var value = message[protoKey];
            var path = root.grpc.getPath(protoKey);
            var node = root.findNode(path);
            if (protoKey != "__numargs") {
                console.log("protoKey = " + protoKey + " path = \"" + path + "\" value = " + value);
            }
            // Use setter and prevent sync!
            node.set(value, true);
        });

        root.grpc.synchronize.on("end", function() {
            // The server has finished sending
            console.log("inexor.tree.grpc.synchronize.end");
            // TODO: here we could stop the Inexor Flex because Inexor Core is gone!
            process.exit();
        });

        root.grpc.synchronize.on("status", function(status) {
            // process status
            console.log("inexor.tree.grpc.synchronize.status: " + status);
        });
        
        root.grpc.initializeTree();

    };
    
    root.grpc.connect();
}

module.exports = {
    Root: Root,
    createTree: createTree
}
