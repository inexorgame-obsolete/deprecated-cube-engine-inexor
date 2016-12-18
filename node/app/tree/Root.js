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
    }
    
    /**
     * @function
     * @name Root.findNode
     * @param {string} path
     * @return {Node}
     */
    findNode(path) {
        let splittedPath = path.split(util.separator);
        let node = this;
        for (let i = 1; i < splittedPath.length; i++) {
            node = node.getChild(splittedPath[i]);
        }
        
        return node;
        // TODO: Use a binary-tree-search-approach?
    }
    
    /**
     * @function
     * @name Root.createRecursive
     * @param {string} path
     * @param {datatype} datatype
     * @param {mixed} initialValue
     * @param {bool} sync
     * @param {bool} readOnly
     * @param {string} protoKey
     */
    createRecursive(path, datatype, initialValue = null, sync = false, readOnly = false, protoKey = null) {
        console.log("path = %s", path);
        let splittedPath = path.split(util.separator);
        var node = this;
        for (let i = 1; i < splittedPath.length - 1; i++) {
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
    
    /**
     * Returns the path of the field by proto key.
     * @function
     * @name Root.grpc.getPath
     * @param {string} protoKey
     * @return {string}
     */

    /**
     * Returns the datatype of the field by proto key.
     * @function
     * @name Root.grpc.getDataType
     * @param {string} protoKey
     * @return {datatype}
     */

    /**
     * Returns the id of the field by proto key.
     * @function
     * @name Root.grpc.getId
     * @param {string} protoKey
     * @return {int}
     */

    /**
     * Loads the field names from .proto and initializes the tree recursively.
     * @function
     * @name Root.grpc.initializeTree
     */

    /**
     * Connects the the server and initializes the tree.
     * @function
     * @name Root.grpc.connect
     */


}

/**
 * Created an Inexor Root Tree
 * @function
 * @name createServer
 * @param server
 * @param grpc
 * @returns {Root}
 */
function createTree(server, grpc) {
    let root = new Root();
    
    root.grpc = {};
    
    // Load the proto definition
    root.grpc.protoDescriptor = grpc.load(__dirname + "/../../../bin/RPCTreeData-inexor.proto");

    // Returns the path of the field by proto key.
    root.grpc.getPath = function(protoKey) {
        return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[protoKey].options["(path)"];
    };

    // Returns the datatype of the field by proto key.
    root.grpc.getDataType = function(protoKey) {
        return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[protoKey].type.name;
    };

    // Returns the id of the field by proto key.
    root.grpc.getId = function(protoKey) {
        return root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName[protoKey].id;
    };

    // Loads the field names from .proto and initializes the tree recursively.
    root.grpc.initializeTree = function() {
        for (var protoKey in root.grpc.protoDescriptor.inexor.tree.TreeService.service.children[0].resolvedRequestType._fieldsByName) {
            try {
                root.createRecursive(root.grpc.getPath(protoKey), root.grpc.getDataType(protoKey), false, true, false, protoKey);
            } catch (err) {
                throw(err);
            }
        }
    };

    // Connects the the server and initializes the tree.
    root.grpc.connect = function() {
        // Connect to the gRPC client
        root.grpc.treeServiceClient = new root.grpc.protoDescriptor.inexor.tree.TreeService("localhost:50051", grpc.credentials.createInsecure());

        root.grpc.synchronize = root.grpc.treeServiceClient.synchronize();

        root.grpc.synchronize.on("data", function(message) {
        	try {
                let protoKey = message.key;
                let value = message[protoKey];
                let path = root.grpc.getPath(protoKey);
                let node = root.findNode(path);
                if (protoKey != "__numargs") {
                    server.log.debug("protoKey = " + protoKey + " path = \"" + path + "\" value = " + value);
                }
                // Use setter and prevent sync!
                node.set(value, true);
        	} catch (err) {
        		server.log.error(err);
        	}
        });

        root.grpc.synchronize.on("end", function() {
            // The server has finished sending
            server.log.debug("inexor.tree.grpc.synchronize.end");
            // TODO: here we could stop the Inexor Flex because Inexor Core is gone!
            process.exit();
        });

        root.grpc.synchronize.on("status", function(status) {
            // process status
            server.log.debug("inexor.tree.grpc.synchronize.status: " + status);
        });
        
        root.grpc.initializeTree();

    };
    
    root.grpc.connect();
    
    return root;
}

module.exports = {
    Root: Root,
    createTree: createTree
}
