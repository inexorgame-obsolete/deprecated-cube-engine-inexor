define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('TabbedNavigationController', ['$scope', '$interval', '$state',
    function ($scope, $interval, $state) {
	  // TODO: Load navigation from app server (RESTAPI) - or - use the states from ui.router
      $scope.tabs = [
        {
          label: "Main Menu",
          state: "/menu/main",
          parentState: ""
        }, {
          label: "Multiplayer",
          state: "/menu/multiplayer",
          parentState: "/menu/main"
        }, {
          label: "Keyboard",
          state: "/test/keyboard",
          parentState: "/menu/main"
        }, {
          label: "UiTest",
          state: "/test/ui",
          parentState: "/menu/main"
        }
      ];

      // The layer states.
      $scope.isVisible = true;
      $scope.isAcceptingKeyInput = true;
      $scope.isAcceptingMouseInput = true;

      // The menu states
      $scope.menuVisible = true;
      $scope.menuState = "/menu/main";
      $scope.menuParentState = "";

      /**
       * Sets the parent state for the given state.
       */
      $scope.setMenuState = function(menuState) {
        $scope.menuState = menuState;
        if (typeof inexor !== "undefined" && inexor.ui) {
          inexor.ui.menuState = menuState;
        }
        for (var tab in $scope.tabs) {
          if (tab['state'] == menuState) {
            var parentState = tab['parentState'];
            $scope.menuParentState = parentState;
            if (typeof inexor !== "undefined" && inexor.ui) {
              inexor.ui.menuParentState = parentState;
            }
            break;
          }
        }
        if (!$state.is(menuState)) {
          $state.transitionTo(menuState);
        }
      };

      $scope.onVisibilityChange = function(isVisible) { $scope.isVisible = isVisible; };
      $scope.onAcceptingKeyInputChange = function(isAcceptingKeyInput) { $scope.isAcceptingKeyInput = isAcceptingKeyInput; };
      $scope.onAcceptingMouseInputChange = function(isAcceptingMouseInput) { $scope.isAcceptingMouseInput = isAcceptingMouseInput; };
      $scope.onMenuVisibilityChange = function(menuVisible) { $scope.menuVisible = menuVisible; };
      $scope.onMenuStateChange = function(menuState) { $scope.setMenuState(menuState); };
      $scope.onMenuParentStateChange = function(menuParentState) { $scope.parentState = parentState; };

      /**
       * Checks the states periodically.
       */
      $scope.syncStates = function() {
        if (typeof inexor !== "undefined" && inexor.ui) {
          var isVisible = inexor.ui.isVisible;
          if ($scope.isVisible != isVisible) {
            $scope.onVisibilityChange(isVisible);
          }
          var isAcceptingKeyInput = inexor.ui.isAcceptingKeyInput;
          if ($scope.isAcceptingKeyInput != isAcceptingKeyInput) {
            $scope.onAcceptingKeyInputChange(isAcceptingKeyInput);
          }
          var isAcceptingMouseInput = inexor.ui.isAcceptingMouseInput;
          if ($scope.isAcceptingMouseInput != isAcceptingMouseInput) {
            $scope.onAcceptingMouseInputChange(isAcceptingMouseInput);
          }
          var menuVisible = inexor.ui.menuVisible;
          if ($scope.menuVisible != menuVisible) {
            $scope.onMenuVisibilityChange(menuVisible);
          }
          var menuState = inexor.ui.menuState;
          if ($scope.menuState != menuState) {
            $scope.onMenuStateChange(menuState);
          }
          var parentState = inexor.ui.parentState;
          if ($scope.parentState != parentState) {
            $scope.onMenuParentStateChange(parentState);
          }
        }
      };

      $interval($scope.syncStates, 100);

    }
  ]);
});
