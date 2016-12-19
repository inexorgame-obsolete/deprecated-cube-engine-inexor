define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('BotMatchMenuController', ['$scope', '$state', '$http', 'MenuService',
    function ($scope, $state, $http, MenuService) {
      console.log("BotMatchMenuController initialized!");
    }
  ]);
});
