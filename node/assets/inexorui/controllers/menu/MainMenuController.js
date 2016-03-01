define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('MainMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {

      $scope.message = "The main menu";
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

      $scope.changeText = function() {
    	  $scope.message = "Text changed!";
      };

      console.log("MainMenuController initialized!");
    }
  ]);
});
