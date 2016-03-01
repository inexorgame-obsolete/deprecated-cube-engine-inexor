define(['./module'], function (directives) {
  'use strict';
  directives.directive('test', function() {
    return {
      template: "<h1>Test directive</h1>"
    };
  });
});
