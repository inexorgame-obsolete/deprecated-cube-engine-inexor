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
      .state('/menu/multiplayer/serverbrowser', {
        url: '/menu/multiplayer/serverbrowser',
        templateUrl: 'inexorui/partials/menu/serverbrowser.html',
        controller: 'ServerBrowserMenuController'
      })
      .state('/menu/edit', {
        url: '/menu/edit',
        templateUrl: 'inexorui/partials/menu/edit.html',
        controller: 'EditMenuController'
      })
      .state('/menu/botmatch', {
        url: '/menu/botmatch',
        templateUrl: 'inexorui/partials/menu/botmatch.html',
        controller: 'BotMatchMenuController'
      })
      .state('/menu/options', {
        url: '/menu/options',
        templateUrl: 'inexorui/partials/menu/options.html',
        controller: 'OptionsMenuController'
      })
      .state('/menu/about', {
        url: '/menu/about',
        templateUrl: 'inexorui/partials/menu/about.html',
        controller: 'AboutMenuController'
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
