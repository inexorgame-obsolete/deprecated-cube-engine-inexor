define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('MainMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {

      $scope.message = "The main menu";
      $scope.connected = false;
      $scope.host = "inexor.nooblounge.net";
      $scope.port = "31415";
      $scope.clientIcon = "";

      $scope.func = function() {
      	MenuService.func();
      };

      $scope.openConsole = function() {
        $state.go('/console');
      };

      $scope.getClientIcon = function() {
        $http.post("/execute", {
          code: "getclienticon"
        }).then(function(response) {
  	      console.log(response);
  	      $scope.clientIcon = response.data;
  	    });  
      };

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

      $scope.changeText = function() {
    	  $scope.message = "Text changed!";
      };

      console.log("MainMenuController initialized!");
    }
  ]);
});
