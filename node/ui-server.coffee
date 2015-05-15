Express = require 'express'
Assets = require "connect-assets"
ServeStatic = require 'serve-static'

App = new Express

App.use ServeStatic "../web"
App.use Assets
  paths: "../web"
  servePath: "/"
  precompile: []
  build: false
  compile: true
  compress: false
  fingerprinting: false

App.listen 8000, "localhost"
