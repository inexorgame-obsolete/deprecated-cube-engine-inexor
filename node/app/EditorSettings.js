/**
 * Settings for the editor.
 */
var EditorSettings = function() {

	var n_rendering = inexor.tree.addChild("rendering", "node");
	var n_rendering_edit = n_rendering.addChild("edit", "node");
	var node_wireframe = n_rendering_edit.addChild("wireframe", "bool", false);
	var node_outline = n_rendering_edit.addChild("outline", "bool", false);

	var editorSettings = {
		
		/**
		 * Sets the wireframe state.
		 * e.g. inexor.editorSettings.setWireframe(true);
		 */
		setWireframe: function(wireframe) {
			node_wireframe = wireframe;
		},

		/**
		 * Sets the outline state.
		 * e.g. inexor.editorSettings.setOutline(true);
		 */
		setOutline: function(outline) {
			node_outline = outline;
		},
		
		onOutline: function(node, oldValue, newValue) {
			console.log("outline (sync'ed): " + newValue);
		}

	};

	node_outline.addPostSyncListener("editorSettings", editorSettings.onOutline);

	setInterval(function() {
		var node_outline = inexor.tree.rendering.edit.getChild("outline");
		node_outline.set(!node_outline.get());
		console.log("Setting outline = " + node_outline.get());
	}, 3 * 1000);

	setInterval(function() {
		var node_wireframe = inexor.tree.rendering.edit.getChild("wireframe");
		node_wireframe.set(!node_wireframe.get());
		console.log("Setting wireframe = " + node_wireframe.get());
	}, 4 * 1000);

	return editorSettings;

};

module.exports = EditorSettings;
