define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('TabbedNavigationController', ['$scope',
    function ($scope) {
	  // TODO: Load navigation from app server (RESTAPI) - or - use the states from ui.router
      $scope.tabs = [
        {
          label: "Main Menu",
          state: "/menu/main"
        }, {
          label: "Multiplayer",
          state: "/menu/multiplayer"
        }, {
          label: "Keyboard",
          state: "/test/keyboard"
        }, {
          label: "UiTest",
          state: "/test/ui"
        }
      ];
      
      $scope.navigationVisible = true;

      $scope.showNavigation = function() {
        $scope.navigationVisible = true;
      };

      $scope.hideNavigation = function() {
        $scope.navigationVisible = false;
      };

    }
  ]);
});
