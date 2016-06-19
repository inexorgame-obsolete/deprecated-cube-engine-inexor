define([
  'angular',
  'angular-animate',
  'angular-hotkeys',
  'angular-resource',
  'angular-ui-bootstrap',
  'angular-ui-router',
  'jq-console',
  './controllers/index',
  './directives/index',
  './filters/index',
  './services/index',
], function (angular) {
  'use strict';
  return angular.module('inexorui', [
    'inexorui.controllers',
    'inexorui.controllers.hud',
    'inexorui.controllers.menu',
    'inexorui.controllers.test',
    'inexorui.directives',
    'inexorui.filters',
    'inexorui.services',
    'ui.router',
    'ui.bootstrap',
    'cfp.hotkeys'
  ]);
});
