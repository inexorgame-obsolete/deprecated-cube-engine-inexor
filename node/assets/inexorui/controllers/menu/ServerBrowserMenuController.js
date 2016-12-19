define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('ServerBrowserMenuController', ['$scope', '$state', '$http', 'ServerManager', 'ConnectionManager',
    function ($scope, $state, $http, ServerManager, ConnectionManager) {

      $scope.ServerManager = ServerManager;

      $scope.connect = function(host, port) {
        ConnectionManager.connect(host, port, function(response) {
          $scope.closeMenu();
        });
      };

      $scope.disconnect = function() {
        ConnectionManager.connect(host, port, function(response) {
          $scope.closeMenu();
        });
      };

      console.log("ServerBrowserMenuController initialized!");

    }
  ]);
});
