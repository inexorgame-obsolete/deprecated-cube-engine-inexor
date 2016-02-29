define(['./inexorui'], function (inexorui) {
  'use strict';
  return inexorui.config(function ($stateProvider, $urlRouterProvider) {
    // The default route
    $urlRouterProvider.otherwise("/main");
    $stateProvider
      .state('/main', {
        url: '/main',
        templateUrl: 'inexorui/partials/mainmenu.html',
        controller: 'MainMenuController'
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
