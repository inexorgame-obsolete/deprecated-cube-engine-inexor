/**
 * Definition of the dependencies.
 */
require.config({

  // The base url of dependencies if not remote
  baseUrl: '/inexorui',
  urlArgs: 'bust=' + (new Date()).getTime(),

  paths: {
    'angular': '../bower_components/angular/angular',
    'angular-animate': '../bower_components/angular-animate/angular-animate',
    'angular-cookies': '../bower_components/angular-cookies/angular-cookies',
    'angular-hotkeys': '../bower_components/angular-hotkeys/build/hotkeys',
    'angular-resource': '../bower_components/angular-resource/angular-resource',
    'angular-sanitize': '../bower_components/angular-sanitize/angular-sanitize',
    'angular-ui-bootstrap': '../bower_components/angular-bootstrap/ui-bootstrap-tpls',
    'angular-ui-router': '../bower_components/angular-ui-router/release/angular-ui-router',
    'bootstrap': '../bower_components/bootstrap/dist/js/bootstrap-tpls',
    'domReady': '../bower_components/domReady/domReady',
    'jq-console': '../bower_components/jq-console/jqconsole.min',
    'jquery': '../bower_components/jquery/dist/jquery',
    'jquery-migrate': '../bower_components/jquery-migrate/jquery-migrate',
  },

  shim: {
    'angular': {
      'deps': ['jquery'],
      'exports': 'angular'
    },
    'angular-ui-router': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'angular-ui-bootstrap': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'angular-animate': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'angular-hotkeys': {
      'deps': ['angular']
    },
    'angular-resource': {
      'deps': ['angular'],
      'exports': 'angular'
    },
    'jq-console': {
      'deps': ['jquery']
    },
    'jquery-migrate': {
      'deps': ['jquery'],
      'exports': 'jquery'
    }
  },
	  
  deps: [
    './inexorui-bootstrap'
  ]

});
