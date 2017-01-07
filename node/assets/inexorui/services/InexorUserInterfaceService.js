define(['./module'], function(services) {
  return services.factory('InexorUserInterfaceService', function() {

    var setState = function(visible, acceptKeyInput) {
      // inexor.inexorui.visible
      if (inexor.inexorui.visible != visible) {
    	  
      }
    };

    return {
      setState: setState,
    };

  });
});
