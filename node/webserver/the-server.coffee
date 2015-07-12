Express = require 'express'
Webapp = require "application-server"

module.exports = ->
  Server = new Express

  # TODO: Allow omitting the webapp
  Server.use "/", new Webapp

  Server
