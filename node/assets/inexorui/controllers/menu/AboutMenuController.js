define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('AboutMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {
      console.log("AboutMenuController initialized!");
    }
  ]);
});
