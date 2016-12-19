define(['./module'], function(services) {
  return services.factory('ConnectionManager', [ '$http', 'ServerManager', function ($http, ServerManager) {

    var connected = false;
    var connectedServer = null;

    var connect = function(host, port, callback) {
      console.log('ConnectionManager: Connecting to ' + host + ':' + port);
      $http.post('/api/execute', {
        code: 'connect ' + host + ' ' + port
      }, {
        timeout: 5000
      }).then(function(response) {
  	    console.log(response);
        connected = true;
        if (callback) {
          try {
            callback(response);
          } catch (e) {
            console.log(e);
          }
        }
      }).catch(function(response) {
        console.log('ConnectionManager: Failed to connect to ' + host + ':' + port);
      });
    };

    var disconnect = function(callback) {
      console.log('ConnectionManager: Attempting to disconnect');
      $http.post('/api/execute', {
        code: 'disconnect'
      }, {
        timeout: 5000
      }).then(function(response) {
        console.log(response);
        connected = false;
        console.log('ConnectionManager: Disconnected')
        if (callback) {
          try {
            callback(response);
          } catch (e) {
            console.log(e);
          }
        }
      }).catch(function(response) {
        console.log('ConnectionManager: Failed to disconnect')
      });
    };

    return {
      connect: connect,
      disconnect: disconnect
    };

  }]);
});
