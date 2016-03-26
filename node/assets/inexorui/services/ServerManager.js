define(['./module'], function(services) {
  return services.factory('ServerManager', [ function () {

    var servers = [
      {
        name: 'NoobLounge 10',
        host: 'inexor.nooblounge.net',
        ip: '148.251.141.13',
        port: 31415,
        mode: 'insta ctf',
        map: 'pandora',
        playerCount: 0,
        maxPlayers: 24,
        ping: 56
      }, {
        name: 'NoobLounge 11',
        host: 'inexor.nooblounge.net',
        ip: '148.251.141.13',
        port: 31515,
        mode: 'insta hold',
        map: 'pandora',
        playerCount: 0,
        maxPlayers: 24,
        ping: 58
      }, {
        name: 'Bristo Square',
        host: '178.62.16.15',
        ip: '178.62.16.15',
        port: 31415,
        mode: 'ctf',
        map: 'dust6',
        playerCount: 0,
        maxPlayers: 12,
        ping: 74
      }
    ];

    var getServers = function() {
      console.log("ServerManager.getServers()");
      return servers;
    };

    var fetchServerList = function() {
      // TODO
      console.log('Fetching the current server list not implemented');
    };

    return {
      getServers: getServers,
      fetchServerList: fetchServerList
    };

  }]);
});
