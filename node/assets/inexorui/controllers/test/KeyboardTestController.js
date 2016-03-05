define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('KeyboardTestController', ['$scope', '$document',
    function ($scope, $document) {

	  $scope.debugKeyEvent = function(t, e) {
        console.log(t);
        console.log(e)
        $scope[t + '_keycode'] = e.keyCode;
        $scope[t + '_charcode'] = e.charCode;
        $scope[t + '_which'] = e.which;
        $scope.$apply();
      };

      $document.on("keydown", function(e) {
        $scope.debugKeyEvent("keydown", e);
      });

      $document.on("keypress", function(e) {
        $scope.debugKeyEvent("keypress", e);
      });

      $document.on("keyup", function(e) {
        $scope.debugKeyEvent("keyup", e);
      });

      console.log("KeyboardTestController initialized!");

    }
  ]);
});
