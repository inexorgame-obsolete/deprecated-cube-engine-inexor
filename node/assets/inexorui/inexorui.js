define([
  'angular',
  'uiRouter',
  './controllers/index',
  './directives/index',
  './filters/index',
  './services/index'
], function (angular) {
  'use strict';
  return angular.module('inexorui', [
    'inexorui.controllers',
    'inexorui.directives',
    'inexorui.filters',
    'inexorui.services',
    'ui.router'
  ]);
});
