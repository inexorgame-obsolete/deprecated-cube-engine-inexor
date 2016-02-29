var Promise = require('promise');
var InexorService = require('./../lib/rpcapi/InexorService.js');

var service = new InexorService();
var messages = service.messages;

// This is a specific express-middleware for proccessing RPC/Cubescript calls
// 1. Construct a new CubeScript message buffer
// 2. Send it via the Inexor Service Provider
// 3. Return stuff!
function EvalCubescript(code) {  
    return new Promise(function(resolve, reject) {
        var msg = new messages.Cubescript(code);
        service.EvalCubescript(msg, function(data) { 
            resolve(data); 
        }); 
    });
}


module.exports = Promise.nodeify(EvalCubescript);
