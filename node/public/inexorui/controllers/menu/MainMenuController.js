define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('MainMenuController', ['$scope', '$state', '$http', 'MenuService', 'HudService',
    function ($scope, $state, $http, MenuService, HudService) {

	  $scope.fullscreen = '1';

      $scope.message = "The main menu";
      $scope.clientIcon = "";

      $scope.func = function() {
      	MenuService.func();
      };

      $scope.execute = function(command, callback) {
        console.log("execute command " + command);
        $http.post("/api/execute", {
          code: command
        }).then(function(response) {
  	      console.log(response);
  	      if (callback) {
  	        callback();
  	      }
  	    });  
      };

      $scope.showConsole = function() {
        HudService.showHud('console');
      };

      $scope.hideConsole = function() {
        HudService.hideHud('console');
      };

      $scope.quit = function() {
        $scope.execute("quit");
      };

      $scope.toggleFullscreen = function() {
        $scope.execute("fullscreen " + $scope.fullscreen);
      };

      $scope.startCoopEditing = function() {
        $scope.execute("coop");
      };

      $scope.startBotMatch = function() {
        $scope.execute("map pandora", function() {
          $scope.execute("addbot 75");
        });
      };

      $scope.getClientIcon = function() {
        $http.post("/api/execute", {
          code: "getclienticon"
        }).then(function(response) {
  	      console.log(response);
  	      $scope.clientIcon = response.data;
  	    });  
      };

      $scope.changeText = function() {
    	  $scope.message = "Text changed!";
      };

      console.log("MainMenuController initialized!");
    }
  ]);
});
