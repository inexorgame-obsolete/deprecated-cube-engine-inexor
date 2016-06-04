/**
 * The HUDManager manages all HUDs.
 */
var HUDManager = function() {

	// Creates "inexor.tree.huds"
	var hudsNode = inexor.tree.addChild("huds", "node");

	return {

		/**
		 * Creates a new HUD with the given name.
		 */
		create = function(name) {

			// Creates "inexor.tree.huds.[name]"
			var hudNode = hudsNode.addChild(name, "node");

			// Creates "inexor.tree.huds.[name].visible"
			hudNode.addChild("visible", "bool", false);

			// Creates "inexor.tree.huds.[name].position"
			hudNode.addChild("position", "string", "bottom right");

			// Creates "inexor.tree.huds.[name].values"
			hudNode.addChild("values", "node");
		},

		/**
		 * Shows the HUD with the given name.
		 * @param name The name of the HUD.
		 */
		show = function(name) {
			var hudNode = hudsNode.getChild(name);
			hudNode.visible = true;
		},

		/**
		 * Hides the HUD with the given name.
		 * @param name The name of the HUD.
		 */
		hide = function(name) {
			var hudNode = hudsNode.getChild(name);
			hudNode.visible = true;
		},

		/**
		 * Sets the position of the HUD with the given name.
		 * @param name The name of the HUD.
		 * @param position The new position of HUD.
		 */
		setPosition = function(name, position) {
			var hudNode = hudsNode.getChild(name);
			hudNode.position = position;
		},

		/**
		 * Adds a new key/value pair for the HUD with the given name.
		 * @param name The name of the HUD.
		 * @param key The key.
		 * @param initialValue The initial value.
		 */
		addValue = function(name, key, datatype, initialValue) {
			var hudNode = hudsNode.getChild(name);
			hudNode.values.addChild(key, datatype, initialValue);
		},

	};
};

module.exports = HUDManager;
