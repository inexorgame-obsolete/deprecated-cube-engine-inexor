/**
 * @tutorial REST-tutorial
 * The IPC Server offers a RESTfull approach to talk to it's C++ backend
 * To communicate with the server use `GET` and `POST` requests respectively.
 * Currently the server uses `text/plain` requests for interaction, which might change in the future.
 * Following methods are currently offered by the API
 * 
 * - `tree/dump` will dump the hierarchical structure of the tree
 * - send a `GET` request to `tree/member` to get a `text/plain` representation of the object
 * - send a `POST` request with `text/plain` in `BODY` to `tree/member` to synchronize specified member (returns either `200` or a failure excerpt)
 */

module.exports = function(...opts) {
    return {
        "get": function(request, response, next) {
            try {
                let node = opts[0].findNode("/" + request.params[0]);
                if (node.isContainer) {
                    response.send(200, node.toString());
                } else {
                    response.send(200, node.get());
                }
            } catch (e) {
                opts[1].log.error(e);
            }
            return next();
        },

        "post": function(request, response, next) {
            try {
                let node = opts[0].findNode("/" + request.context[0]);
                node.set(request.body);
                response.send(200);
            } catch (e) {
                opts[1].log.error(e);
            }
            return next();
        },

        "delete": function(request, response, next) {
            try {
                let node = opts[0].findNode("/" + request.context[0]);
                let parentNode = node.getParent();
                parentNode.removeChild(node._name);
                response.send(200);
            } catch (e) {
                opts[1].log.error(e);
            }
            return next();
        },

        "dump": function(request, response, next) {
            try {
                response.send(opts[0].toString());
            } catch (e) {
                opts[1].log.error(e);
            }
            return next();
        }
    }
}
