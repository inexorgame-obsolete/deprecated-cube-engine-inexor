define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('OptionsMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {

	  $scope.fullscreen = false;

      $scope.toggleFullscreen = function() {
        $scope.fullscreen = !$scope.fullscreen;
        $http.post("/api/execute", {
          code: "fullscreen " + ($scope.fullscreen ? "1" : "0")
        }).then(function(response) {
        });  
      };

      console.log("OptionsMenuController initialized!");
    }
  ]);
});
