/**
 * Settings for the editor.
 */
function EditorSettings(tree, server) {

	var editorSettings = {
		
		/**
		 * Sets the wireframe state.
		 * e.g. inexor.editorSettings.setWireframe(true);
		 */
		setWireframe: function(wireframe) {
			tree.wireframe = wireframe;
		},

		/**
		 * Sets the outline state.
		 * e.g. inexor.editorSettings.setOutline(true);
		 */
		setOutline: function(outline) {
			tree.outline = outline;
		},
		
		onOutline: function(node, oldValue, newValue) {
			server.log.debug("outline (sync'ed): " + newValue);
		}

	};

	tree.getChild("outline").addListener("postSync", editorSettings.onOutline);

	setInterval(function() {
		var node = tree.getChild("outline");
		var oldValue = node.get();
		if (node.get() == 0) {
			node.set(1);
		} else {
			node.set(0);
		}
		server.log.debug("Setting outline = " + node.get() + " (was: " + oldValue + ")");
	}, 30 * 1000);

	setInterval(function() {
		var node = tree.getChild("wireframe");
		var oldValue = node.get();
		if (node.get() == 0) {
			node.set(1);
		} else {
			node.set(0);
		}
		server.log.debug("Setting wireframe = " + node.get() + " (was: " + oldValue + ")");
	}, 45 * 1000);

	return editorSettings;
};

module.exports = EditorSettings;
