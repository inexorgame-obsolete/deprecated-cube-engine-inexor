define(['./module'], function(services) {
  return services.factory('MenuService', function () {
    var func = function() {
      console.log('called "MenuService.func()"');
    };
    return {
      func: func
    };
  });
});
