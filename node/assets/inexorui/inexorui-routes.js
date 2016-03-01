define(['./inexorui'], function (inexorui) {
  'use strict';
  return inexorui.config(function ($stateProvider, $urlRouterProvider) {
    // The default route
    $urlRouterProvider.otherwise("/menu/main");
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
      .state('/console', {
        url: '/console',
        templateUrl: 'inexorui/partials/console.html',
        controller: 'ConsoleController'
      })
      .state('/test/keyboard', {
        url: '/test/keyboard',
        templateUrl: 'inexorui/partials/test/keyboard.html',
        controller: 'KeyboardTestController'
      });
  });
});
