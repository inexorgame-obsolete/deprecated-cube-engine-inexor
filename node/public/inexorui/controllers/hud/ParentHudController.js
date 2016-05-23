define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('ParentHudController', ['$scope', '$document', 'HudService',
    function ($scope, $document, HudService) {

	  $scope.registerHud = function(name, visible, x, y, w, h, defaultHotkey) {
		HudService.registerHud(name, visible, x, y, w, h, defaultHotkey);
	  };

	  /**
	   * Shows the HUD with the given name.
	   * @param The HUD name.
	   */
      $scope.showHud = function(name) {
        HudService.showHud(name);
      };

	  /**
	   * Hides the HUD with the given name.
	   * @param The HUD name.
	   */
      $scope.hideHud = function(name) {
        HudService.hideHud(name);
      };

	  /**
	   * Toggles the HUD with the given name.
	   * @param The HUD name.
	   */
      $scope.toggleHud = function(name) {
        HudService.toggleHud(name);
      };

      console.log('ParentHudController initialized!');

    }
  ]);
});
