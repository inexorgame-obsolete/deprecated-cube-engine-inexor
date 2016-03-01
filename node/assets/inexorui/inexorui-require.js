/**
 * Definition of the dependencies.
 */
require.config({

  // The base url of dependencies if not remote
  baseUrl: '/inexorui',

  // Paths to the remote and local dependencies
  // TODO: local first, if not available, use the remote dependency
  paths: {
    'jquery': ['//cdnjs.cloudflare.com/ajax/libs/jquery/2.2.1/jquery.min', 'libs/jquery-min'],
    'jquery-migrate': ['//cdnjs.cloudflare.com/ajax/libs/jquery-migrate/1.4.0/jquery-migrate.min', 'libs/jquery-migrate'],
    'domReady': ['//cdnjs.cloudflare.com/ajax/libs/require-domReady/2.0.1/domReady.min', 'libs/domReady'],
    'bootstrap': ['//cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.6/js/bootstrap.min', 'libs/bootstrap-min'],
    'angular': ['//cdnjs.cloudflare.com/ajax/libs/angular.js/1.3.20/angular', 'libs/angularjs/angular.min'],
    'uiBootstrap': ['//cdnjs.cloudflare.com/ajax/libs/angular-ui-bootstrap/1.2.1/ui-bootstrap-tpls.min', 'libs/angular-ui-bootstrap/ui-bootstrap-tpls.min'],
    'hotkeys': ['//cdnjs.cloudflare.com/ajax/libs/angular-hotkeys/1.7.0/hotkeys.min', 'libs/angular-hotkeys/hotkeys.min'],
    'uiRouter': ['//cdnjs.cloudflare.com/ajax/libs/angular-ui-router/0.2.18/angular-ui-router', 'libs/angular-ui-router'],
    'ngResource': ['//cdnjs.cloudflare.com/ajax/libs/angular.js/1.3.20/angular-resource', 'libs/angularjs/angular-resource.min'],
    'jqconsole': ['//cdnjs.cloudflare.com/ajax/libs/jq-console/2.7.7/jqconsole.min', 'libs/jq-console/jqconsole'],
    'inexorui': ['inexorui-app']
  },

  shim: {
    'angular': {
      'deps': ['jquery'],
      'exports': 'angular'
    },
    'uiRouter': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'uiBootstrap': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'ngResource': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'jqconsole': {
      'deps': ['jquery']
    },
    'jquery-migrate': {
      'deps': ['jquery'],
      'exports': 'jquery'
    },
    'hotkeys': {
      'deps': ['angular']
    }
  },

  deps: [
    './inexorui-bootstrap'
  ]

});
