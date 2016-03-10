define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('ServerBrowserMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {
      console.log("ServerBrowserMenuController initialized!");
    }
  ]);
});
