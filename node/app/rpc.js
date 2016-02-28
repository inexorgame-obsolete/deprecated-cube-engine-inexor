var Promise = require('promise');
var InexorService = require('./../lib/rpcapi/InexorService.js');

var service = new InexorService();
var messages = service.messages;

// This is a specific express-middleware for proccessing RPC/Cubescript calls
// 1. Construct a new CubeScript message buffer
// 2. Send it via the Inexor Service Provider
// 3. Convert the response to CubeScript message buffer and return it
function EvalCubescript(code) {  
    var msg = new messages.Cubescript(code);
    return new Promise(service.EvalCubescript(msg, function(a) {
        console.log(a);
        return a;
    }));
}

module.exports = Promise.nodeify(EvalCubescript);
