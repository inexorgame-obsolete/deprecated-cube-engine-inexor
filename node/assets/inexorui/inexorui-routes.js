define(['./inexorui'], function (inexorui) {
  'use strict';
  return inexorui.config(function ($stateProvider, $urlRouterProvider) {
    // The default route
    $urlRouterProvider.otherwise("/menu/main");
    // Definition of the routes: state name, state url, partial template url, controller name
    $stateProvider
      .state('/menu/main', {
        url: '/menu/main',
        templateUrl: 'inexorui/partials/menu/main.html',
        controller: 'MainMenuController'
      })
      .state('/menu/multiplayer', {
        url: '/menu/multiplayer',
        templateUrl: 'inexorui/partials/menu/multiplayer.html',
        controller: 'MultiplayerMenuController'
      })
      .state('/test/keyboard', {
        url: '/test/keyboard',
        templateUrl: 'inexorui/partials/test/keyboard.html',
        controller: 'KeyboardTestController'
      })
      .state('/test/ui', {
        url: '/test/ui',
        templateUrl: 'inexorui/partials/test/ui.html',
        controller: 'UiTestController'
      });
  });
});
