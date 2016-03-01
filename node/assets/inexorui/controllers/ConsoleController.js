define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('ConsoleController', ['$scope', '$http',
    function ($scope, $http) {

	  // TODO: F11 fullscreen console
	  // TODO: F12 quake-like console ()
	  // TODO: move console to service (component should live even when the controller is not active)

	  $scope.jqconsole = angular.element('#console').jqconsole('Inexor CubeScript Console\n', '>>> ');

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

      console.log('ConsoleController initialized!');

    }
  ]);
});
