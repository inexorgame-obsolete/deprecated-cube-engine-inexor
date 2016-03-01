define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('MainMenuController', ['$scope', '$state', '$http', 'MenuService', 'HudService',
    function ($scope, $state, $http, MenuService, HudService) {

      $scope.message = "The main menu";
      $scope.clientIcon = "";

      $scope.func = function() {
      	MenuService.func();
      };

      $scope.showConsole = function() {
        HudService.showHud('console');
      };

      $scope.hideConsole = function() {
        HudService.hideHud('console');
      };

      $scope.getClientIcon = function() {
        $http.post("/execute", {
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
