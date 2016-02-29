define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('MainMenuController', ['$scope', '$state', 'MenuService',
    function ($scope, $state, MenuService) {

      $scope.data = "The main menu";

      $scope.func = function() {
      	MenuService.func();
      };

      $scope.openConsole = function() {
    	  $state.go('/console');
      };

      $scope.changeText = function() {
    	  $scope.data = "Text changed!";
      };

      console.log("MainMenuController initialized!");
    }
  ]);
});
