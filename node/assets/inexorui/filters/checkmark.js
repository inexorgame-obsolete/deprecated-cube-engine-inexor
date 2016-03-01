define(['./module'], function (filters) {
  'use strict';
  return filters.filter('checkmark', function (version) {
    return function (input) {
      return input ? '\u2713' : '\u2718';
    }
  });
});
