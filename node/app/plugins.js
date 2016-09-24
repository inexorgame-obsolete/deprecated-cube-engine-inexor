const PLUGIN_FOLDER = 'plugins';
const RESERVED_PLUGINS = ['grpc', 'rest']; // These can only be registered from app/plugins/ folder
// TODO: Block grpc from beeing writable. Implement sync / nonsync

/**
 * @function registerPlugins
 * @param {array} plugins - The list of plugins to load
 * @param {Root} inexor - the inexor root object
 **/
function registerPlugins(plugins, inexor) {
  return new Promise(function(resolve, reject) {
    //Depending wether plugins-xy or inexor-plugins-xy is used, it is loaded from either app/plugins or NPM

    plugins.forEach(function(pluginName) {
        let names = pluginName.split('-');
        let name = names[names.length -1]; // The last element
        let path = '';

        if (names[0] == 'inexor') {
            if (RESERVED_PLUGINS.includes(name)) return; // This should jump directly to the next forEach element?
            path = pluginName;
        } else {
            path = './plugins/' + name;
        }

        try {
          // Read the meta data from package
          let pluginMeta = require(path + '/package.json');
          var plugin = require(path)(tree, server);
        } catch(Exception) {
          reject(Exception)
        }

        // let sync = (typeof(pluginMeta.plugin.sync) === 'boolean') ? pluginMeta.plugin.sync : false; // Set default to false
        // inexor.tree.addChild(name, 'node', plugin, sync, false);
        inexor.tree[name] = plugin;

        if (pluginMeta.plugin.hasOwnProperty('routes')) {
            for (routeType in pluginMeta.plugin.routes) {
                for (route in pluginMeta.plugin.routes[routeType]) {
                    // TODO: This is not generic and needs improvement..
                    let func = pluginMeta.plugin.routes[routeType][route]; // Function name

                    switch (routeType) {
                    case 'get':
                        inexor.server.get(route, inexor.tree[name][func]);
                        break;
                    case 'set':
                        inexor.server.post(route, inexor.tree[name][func]);
                        break;
                    }
              }
          }
        }
      }

      resolve('Loaded ' + plugins.length + ' plugins successfully.')
    })
}

module.exports = registerPlugins
