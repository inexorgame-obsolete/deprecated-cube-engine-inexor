define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('TestHudController', ['$scope',
    function ($scope) {

	  $scope.registerHud('test', false, '0px', '0px', '100%', '250px', 'F10');

      // Fake value
      $scope.fps = 60;

      console.log('TestHudController initialized!');
    }
  ]);
});
