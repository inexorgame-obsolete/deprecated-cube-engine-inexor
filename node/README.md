# Inexor node application server

This is the Inexor node application server, delivered with Inexor to serve RPC requests.

## Introduction
The Inexor IPC Client is merely a tool to interact with our `C/C++` backend over a decent web-technology easily.
A deep introduction into the topic and the technology behind can be found [at following wiki article](https://github.com/inexor-game/code/wiki/Inexor-Tree-API).

## How to run 
You normally do start the IPC interface with the following routine
1. Run an Inexor Client that is [either compiled against gRPC](https://github.com/inexor-game/code/wiki/gluegen-gluecode-setup-(on-Linux-at-least), or runs on 0.8+
2. Start the IPC server with the respective `inexor_node_unix` or `inexor_node_windows.bat` script

## How to develop with the IPC service
The IPC Server offers a RESTfull approach to talk to it's C++ backend.
To communicate with the server use `GET` and `POST` requests respectively.
Currently the server uses `text/plain` requests for interaction, which might change in the future.
Following methods are currently offered by the API
 
 - `tree/dump` will dump the hierarchical structure of the tree
 - send a `GET` request to `tree/member` to get a `text/plain` representation of the object
 - send a `POST` request with `text/plain` in `BODY` to `tree/member` to synchronize specified member (returns either `200` or a failure excerpt)
 
## Roadmap and TODO
Of course this is provisional and a lot of things are likely to differ, but I'll list the important changes here
  - ~~Fix the `inexor_node_unix` script~~
  - ~~Fix: the server should either exit or reboot once `/tmp/inexor.socket` has been touched~~
  - ~~Fix: use a single response model for the RPC client~~
  - ~~Enhance: send and receive commands via jq-console~~
  - ~~Optionally: implement [browserify](http://browserify.org/) to deliver our dependencies~~
  - ~~Future: implement a [node-tree API](https://github.com/inexor-game/code/wiki/Inexor-Tree-API#nodejs-implenentation) which will replace RPC/ICP~~
  - Release: design a GUI, ~~replace that CubeScript stuff~~
  - For 0.9: Implement a plugin system, add OAuth and package deployment on top of it

