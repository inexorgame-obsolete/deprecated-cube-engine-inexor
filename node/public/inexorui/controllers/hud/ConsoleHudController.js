define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('ConsoleHudController', ['$scope', '$http', 'hotkeys',
    function ($scope, $http, hotkeys) {

	  // TODO: F11 fullscreen console
	  // TODO: F12 quake-like console ()
	  // TODO: move console to service (component should live even when the controller is not active)

	  $scope.registerHud('console', false, '0px', '0px', '100%', '250px', 'F12');

	  $scope.jqconsole = angular.element('#hud-console-widget').jqconsole('Inexor CubeScript Console\n', '>>> ');

      $scope.execute = function(input) {
        $http.post('/api/execute', {
          code: input
        }, {
          timeout: 1000
        }).then(function(response) {
          // Output the result with the class jqconsole-output.
          console.log(response);
          $scope.jqconsole.Write(response + '\n', 'jqconsole-output');
          // Restart the prompt.
          $scope.startPrompt();
        }).catch(function(data) {
          // Handle error
          $scope.jqconsole.Write('Unable to execute command "' + input + '"\n', 'jqconsole-output');
          console.log(data);
          // Restart the prompt.
          $scope.startPrompt();
        });  
      };

      $scope.startPrompt = function () {
        // Start the prompt with history enabled.
        $scope.jqconsole.Prompt(true, function (input) {
          // Execute the input
          $scope.execute(input);
        });
      };
      $scope.startPrompt();

      hotkeys.add({
        combo: 'ctrl+f12',
        callback: function() {
          console.log('Toggle console');
          $scope.toggleHud('console');
        }
      });

      console.log('ConsoleHudController initialized!');

    }
  ]);
});
