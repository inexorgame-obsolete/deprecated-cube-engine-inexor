/**
 * Settings for the editor.
 */
function EditorSettings() {

	var editorSettings = {
		
		/**
		 * Sets the wireframe state.
		 * e.g. inexor.editorSettings.setWireframe(true);
		 */
		setWireframe: function(wireframe) {
			inexor.tree.wireframe = wireframe;
		},

		/**
		 * Sets the outline state.
		 * e.g. inexor.editorSettings.setOutline(true);
		 */
		setOutline: function(outline) {
			inexor.tree.outline = outline;
		},
		
		onOutline: function(node, oldValue, newValue) {
			console.log("outline (sync'ed): " + newValue);
		}

	};

	inexor.tree.getChild("outline").addPostSyncListener("editorSettings", editorSettings.onOutline);

	setInterval(function() {
		var node = inexor.tree.getChild("outline");
		var oldValue = node.get();
		if (node.get() == 0) {
			node.set(1);
		} else {
			node.set(0);
		}
		console.log("Setting outline = " + node.get() + " (was: " + oldValue + ")");
	}, 30 * 1000);

	setInterval(function() {
		var node = inexor.tree.getChild("wireframe");
		var oldValue = node.get();
		if (node.get() == 0) {
			node.set(1);
		} else {
			node.set(0);
		}
		console.log("Setting wireframe = " + node.get() + " (was: " + oldValue + ")");
	}, 45 * 1000);

	return editorSettings;
};

module.exports = EditorSettings;
