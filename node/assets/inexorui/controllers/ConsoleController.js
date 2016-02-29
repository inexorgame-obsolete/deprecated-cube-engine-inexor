define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('ConsoleController', ['$scope',
    function ($scope) {
      $scope.func = function() {
      	console.log("called ConsoleController.func()");
      };
      $scope.data = "The console";
      console.log("ConsoleController initialized!");
    }
  ]);
});
