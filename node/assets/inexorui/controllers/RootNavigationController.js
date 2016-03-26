define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('RootNavigationController', ['$scope', '$interval', '$timeout', '$state',
    function ($scope, $interval, $timeout, $state) {
	  // TODO: Load navigation from app server (RESTAPI) - or - use the states from ui.router
      $scope.tabs = [
        {
          label: 'Main Menu',
          state: '/menu/main',
          parentState: ''
        }, {
          label: 'Multiplayer',
          state: '/menu/multiplayer',
          parentState: '/menu/main'
        }, {
          label: 'Keyboard',
          state: '/test/keyboard',
          parentState: '/menu/main'
        }, {
          label: 'UiTest',
          state: '/test/ui',
          parentState: '/menu/main'
        }
      ];

      // The layer states.
      $scope.isVisible = true;
      $scope.isAcceptingKeyInput = true;
      $scope.isAcceptingMouseInput = true;

      // The menu states
      $scope.isMenuVisible = true;
      $scope.menuState = '/menu/main';
      $scope.menuParentState = '';

      /**
       * Sets the parent state for the given state.
       */
      $scope.setMenuState = function(menuState, synchronize) {
        console.log('Setting menu state: ' + menuState)
        $scope.menuState = menuState;
        if (synchronize != false, typeof inexor !== 'undefined') {
          try {
            inexor.ui.menuState = menuState;
            // TODO: send state back
          } catch (e) {
            console.log('Failed to set the menu state!');
          }
        }
        for (var tab in $scope.tabs) {
          if (tab['menuState'] == menuState) {
            var parentState = tab['menuParentState'];
            $scope.menuParentState = parentState;
            if (synchronize != false, typeof inexor !== 'undefined') {
              inexor.ui.menuParentState = parentState;
              // TODO: send state back
            }
            break;
          }
        }
        if (!$state.is(menuState)) {
          console.log('Transition to: ' + menuState);
          $state.transitionTo(menuState);
        }
      };

      $scope.closeMenu = function() {
        $scope.isMenuVisible = false;
        $scope.menuState = '/menu/main';
        $scope.menuParentState = '';
      }

      $scope.onVisibilityChange = function(isVisible) { $scope.isVisible = isVisible; };
      $scope.onAcceptingKeyInputChange = function(isAcceptingKeyInput) { $scope.isAcceptingKeyInput = isAcceptingKeyInput; };
      $scope.onAcceptingMouseInputChange = function(isAcceptingMouseInput) { $scope.isAcceptingMouseInput = isAcceptingMouseInput; };
      $scope.onMenuVisibilityChange = function(isMenuVisible) { $scope.isMenuVisible = isMenuVisible; };
      $scope.onMenuStateChange = function(menuState) { $scope.setMenuState(menuState, false); };
      $scope.onMenuParentStateChange = function(menuParentState) { $scope.parentState = parentState; };

      $scope.uiEventHandler = function(event_name, value) {
        console.log(event_name);
        console.log(value);
        switch (event_name) {
          case 'isVisible':
            $scope.onVisibilityChange(value);
            break;
          case 'isAcceptingKeyInput':
            $scope.onAcceptingKeyInputChange(value);
            break;
          case 'isAcceptingMouseInput':
            $scope.onAcceptingMouseInputChange(value);
            break;
          case 'isMenuVisible':
            $scope.onMenuVisibilityChange(value);
            break;
          case 'menuState':
            $scope.onMenuStateChange(value);
            break;
          case 'menuParentState':
            $scope.onMenuParentStateChange(value);
            break;
        }
      };

      try {
        $timeout(function() {
          window.registerEventHandler($scope.uiEventHandler); // 'uiVisible', 
        }, 1000);
      } catch (e) {
        console.log(e);
      }

    }
  ]);
});
