# Inexor: Javascript components

```
../inexor_node_unix [port] [ip]
```

This starts the main node application, which provides the
web application and the HTTP API.

* port – The port to listen to; DEFAULT: 48702
* ip – The IP address to bind to. Set to all in order to
  bind to all available IPs;  DEFAULT: "localhost"

```
subsystem_start rpc
subsystem_start cef
```

Start the RPC interface and the web GUI in inexor.
The node server (above) must be started before this and it
only works if we're listening to the default interface.

## What is this?

This folder contains all of inexors components written in
javascript (coffeescript actually, but it compiles to JS).

This contains the web application that is the interface of
inexor; it is both used as the (future) default ingame
interface for inexor and as a web interface which can be
used to remote-control inexor or a game server.

The web application's server is written in node; this node
application will in future also implement various features
(e.g. master server, ingame chat, plugins directory,
automatic map detection, ...) and a scripting interface for
inexor.

Then, we also provide a few generic utilities and javascript
bindings for the inexor RPC (google protobuf) API and the
node.js applications http API. (The protobuf API is a direct
connection to inexor with a much better performance, but is
much more low level. The HTTP API is easier to use and
provides more features, but with a lot less performance).

## webserver/

This essentially contains the node.js application, which at
the moment provides the server for the web UI and the server
for the inexor HTTP API.

JS/Coffee files under lib/ and webserver/ can be required.

It  is started via the bin/serve command, but in order to
get the NODE_PATHS right, you should start it via 

## webui/

This contains the Angular based web app we show as UI.
The JS/coffeescript files from lib/ and webui/lib can be
used.

* `webui/main` Contains the main HTML site and the bootsrtap
  code we're always on.
* `webui/lib` contains all the JS code specific to the web
  app.
* `webui/components` contains reusable directives
* `webui/windows` contains all the windows/guis we have.

