define([
  'angular',
  'uiRouter',
  './controllers/index',
  './services/index'
], function (angular) {
  'use strict';
  return angular.module('inexorui', [
    'inexorui.controllers',
    'inexorui.services',
    'ui.router'
  ]);
});
