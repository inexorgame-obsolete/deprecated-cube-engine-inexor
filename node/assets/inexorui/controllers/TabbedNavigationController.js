define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('TabbedNavigationController', ['$scope',
    function ($scope) {
	  // TODO: Load navigation from app server (RESTAPI) 
      $scope.tabs = [
        {
          label: "Main Menu",
          state: "/menu/main"
        }, {
          label: "Multiplayer",
          state: "/menu/multiplayer"
        }, {
          label: "Console",
          state: "/console"
        }, {
          label: "Keyboard",
          state: "/test/keyboard"
        }
      ];
    }
  ]);
});
