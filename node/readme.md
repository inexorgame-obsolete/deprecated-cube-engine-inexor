#Inexor node application server

This is the Inexor node application server, delivered with Inexor to serve RPC requests.
##About
The following server is a simple re-write of the previous node webserver. It's aims are
 - simplicity
 - usability
 - fully functional.

##How to use it
You can start the server with the following syntax
 1. Make sure Inexor runs and listens for IPC-connections, use `subsystem_start rpc` if it doesn't.
 2. The following applies under linux
  - install all requirements with `npm install`
  - run the server with `node app/app.js`
  - you can specify optional commands and a configuration file, have a look at `node app/app.js -h`

##Organizational things for web/node-developers
The server does the following at the moment

 - Serve all static files from `node/assets`
 - Handle a static post route at `localhost:48702/execute`
  - You can fire an event using `Content-type: application/json`
  - Basically every valid JSON keypair will be executed, eg: `json { "code": "echo\"test\"" }`

I have specifically created this server to be lightweight (very few dependencies) and easy to understand.

We ship [jq-console](https://github.com/replit/jq-console), which shall the replacement for the existing CubeScript command-line.
##Roadmap and TODO
Of course this is provisional and a lot of things are likely to differ, but I'll list the important changes here
  - Fix the `inexor_node_unix` script
  - Fix: the server should either exit or reboot once `/tmp/inexor.socket` has been touched
  - Fix: use a single response model for the RPC client
  - Enhance: send and receive commands via jq-console
  - Optionally: implement [browserify](http://browserify.org/) to deliver our dependencies
  - Future: implement a [node-tree API](https://github.com/inexor-game/code/wiki/Inexor-Tree-API#nodejs-implenentation) which will replace RPC/ICP
  - Release: design a GUI, replace that CubeScript stuff

