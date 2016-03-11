define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('EditMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {

      $scope.coop = function() {
        $http.post("/api/execute", {
          code: "coop"
        }).then(function(response) {
          console.log(response);
          $scope.connected = false;
        });  
      };

	  console.log("EditMenuController initialized!");
    }
  ]);
});
