define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('MultiplayerMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {

      $scope.connected = false;
      $scope.host = "inexor.nooblounge.net";
      $scope.port = "31415";

      $scope.connect = function() {
        $http.post("/api/execute", {
          code: "connect " + $scope.host + " " + $scope.port
        }).then(function(response) {
  	      console.log(response);
          $scope.connected = true;
        });  
      };

      $scope.disconnect = function() {
        $http.post("/api/execute", {
          code: "disconnect"
        }).then(function(response) {
          console.log(response);
          $scope.connected = false;
        });  
      };

      // TODO: getHost, getPort

      console.log("MultiplayerMenuController initialized!");
    }
  ]);
});
