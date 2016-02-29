require.config({

  baseUrl: '/inexorui',

  paths: {
    'jquery': ['//ajax.googleapis.com/ajax/libs/jquery/2.0.3/jquery', 'libs/jquery-min'],
    'domReady': ['//cdnjs.cloudflare.com/ajax/libs/require-domReady/2.0.1/domReady.min', 'libs/domReady'],
    'bootstrap': ['//netdna.bootstrapcdn.com/bootstrap/3.0.2/js/bootstrap', 'libs/bootstrap-min'],
    'angular': ['//cdnjs.cloudflare.com/ajax/libs/angular.js/1.3.20/angular', 'libs/angularjs/angular.min'],
    'uiRouter': ['//cdnjs.cloudflare.com/ajax/libs/angular-ui-router/0.2.18/angular-ui-router', 'libs/angular-ui-router'],
    'ngResource': ['//cdnjs.cloudflare.com/ajax/libs/angular.js/1.3.20/angular-resource', 'libs/angularjs/angular-resource.min'],
    'inexorui': ['inexorui']
  },

  shim: {
    'angular': {
      'exports': 'angular'
    },
    'uiRouter': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'ngResource': {
      'deps': ['angular'],
      'exports': 'angular'
    }
  },

  deps: [
    './inexorui-bootstrap'
  ]

});
