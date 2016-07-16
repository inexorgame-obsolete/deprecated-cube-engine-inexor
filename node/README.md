# Inexor node application server

This is the Inexor node application server, delivered with Inexor to serve RPC requests.

## Introduction
The Inexor IPC Client is merely a tool to interact with our `C/C++` backend over a decent web-technology easily.
A deep introduction into the topic and the technology behind can be found [at following wiki article](https://github.com/inexor-game/code/wiki/Inexor-Tree-API).

## How to run 
Normally you ain't touch this any more since the server is started automagically for you, and everything should be ready-to-go..
If you ever occur to manually start the IPC client, please follow the routine below

1. Run an Inexor Client that is [either compiled against gRPC](https://github.com/inexor-game/code/wiki/gluegen-gluecode-setup-(on-Linux-at-least)), or runs on at least Steroids Edition..
2. Start the IPC server with the respective `inexor_node_unix` or `inexor_node_windows.bat` script

## Interacting directly with the Inexor REST API
The IPC Server offers a RESTfull approach to talk to it's C++ backend.
To communicate with the server you have to use `GET` and `POST` requests to the HTTP server with prefix `tree/` respectively.
Currently the server uses `text/plain` requests for interaction, which might change in the future.
Following methods are currently available

#### Dumping the Inexor tree
By sending a `GET` request to `/tree/dump` you will receive a hierarchical structure of the tree

#### Reading tree members
You can read the state of a tree member by sending a `GET` request to `tree/membername`

#### Updating tree members
You can update the state of a tree member by sending a `POST` request to `tree/membername`
The request should be in `text/plain`, the message should be in `BODY`
Depending on if your request was successfull, you either receive `200`, or a detailed failure report.

#### ~~Deleting tree members~~
~~ You can delete a tree member by sending a `POST` request to `/tree/delete` containing the member name in the `BODY`~~
This feature is not-yet implemented, as it is highly under discussion.

## How to write plugins for the server
The following short introduction should give an introduction covers how-to write plugins for Inexor IPC server.

#### Read through Node.js modules sections carefully
Inexor's IPC server builds on top of [Node.js modules](https://nodejs.org/api/modules.html) and [NPM](https://docs.npmjs.com/getting-started/creating-node-modules), therefore it is good to know what you're doing.

#### Creating a boilerpalette `index.js`
Following is a boilerpalette code for your plugin, which I'll explain briefly

```
module.exports = function(tree) {
	return: {
		// something goes here
	}
}
```

This is the single entry point you'll want to expose to Inexor so we'll be able to read your plugin later-on..
An ``instanceof`` inexor.Tree will be passed alongside any plugin, so it can build upon.

#### Add a `package.json`
There is no direct dependency needed to write a plugin.
Anyhow you can pull `inexor-tree` from the NPM registry, if you'd like to use our base library (including utils to work with the tree).
You need to choose a name like `inexor-plugin-yourname`, which is important for autoloading our plugins.
Please note that following names are currently reserved

- tree
- auth
- deploy
- master

Other than this we do not dictate any restriction.


#### Add your plugin to the `plugins.json`
The `plugins.json` file that comes with the Inexor IPC server needs to be added, and the name of your plugin (folder) needs to be inserted.
Gotcha. Your plugin should now be automagically loaded and registered in the inexor tree (available via '/yourname' in the tree).

## Roadmap and TODO
Of course this is provisional and a lot of things are likely to differ, but I'll list the important changes here
  - ~~Fix the `inexor_node_unix` script~~
  - ~~Fix: the server should either exit or reboot once `/tmp/inexor.socket` has been touched~~
  - ~~Fix: use a single response model for the RPC client~~
  - ~~Enhance: send and receive commands via jq-console~~
  - ~~Optionally: implement [browserify](http://browserify.org/) to deliver our dependencies~~
  - ~~Future: implement a [node-tree API](https://github.com/inexor-game/code/wiki/Inexor-Tree-API#nodejs-implenentation) which will replace RPC/ICP~~
  - Release: design a GUI, ~~replace that CubeScript stuff~~
  - Plugin autoloader -> naming convention -> add examples (OAuth) and unit tests

