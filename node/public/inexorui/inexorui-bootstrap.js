/**
 * Bootstraps angular onto the window.document node.
 * NOTE: The ng-app attribute should not be on the index.html when using angular.bootstrap
 */
define([
  'require',
  'jquery-migrate',
  'angular',
  'inexorui',
  'inexorui-routes'
], function (require, jquery, angular) {
  'use strict';

  /*
   * place operations that need to initialize prior to app start here
   * using the `run` function on the top-level module
   */
  require([
    'domReady!'
  ], function (document) {
    angular.bootstrap(document, ['inexorui']);
  });

});
