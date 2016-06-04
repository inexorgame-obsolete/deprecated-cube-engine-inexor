/** Inexor Tree **/

var TreeTest = function(tree) {

	// Some tests on the inexor tree
	tree.rendering.addChild("fullscreen", "bool", true);
	tree.addChild("gameplay", "node");
	tree.getChild("gameplay").addChild("gamemodes", "node");
	tree.gameplay.gamemodes.addChild("instactf", "node");
	tree.gameplay.gamemodes.instactf.addChild("test", "string", "a");
	console.log(inexor.tree.gameplay.gamemodes.instactf.test);
	tree.gameplay.gamemodes.instactf.test = "b";
	console.log(inexor.tree.gameplay.gamemodes.instactf.test);
	tree.findNode("/gameplay/gamemodes/instactf/test").set("c");
	console.log(inexor.tree.findNode("/gameplay/gamemodes/instactf/test").get());
	console.log(inexor.tree.gameplay.gamemodes.instactf.test);
	tree.addChild("debug", "bool", true);
	
	var preSetListener = function(node, oldValue, newValue) {
		if (newValue == "b" && oldValue == "a") {
			return true;
		} else if (newValue == "c" && oldValue == "b") {
			return true;
		} else if (newValue == "a" && oldValue == "c") {
			return true;
		}
		console.log("blocked!");
		return false;
	};

	var postSetListener = function(node, oldValue, newValue) {
		console.log("tree.gameplay.gamemodes.instactf.test = " + newValue);
	}

	var handler = "treeTest";
	var testNode = tree.gameplay.gamemodes.instactf.getChild("test"); // we want the node not the value!
	testNode.addPreSetListener(handler, preSetListener);
	testNode.addPostSetListener(handler, postSetListener);

	/*
	var rotateTestNode = function() {
		var testNode = tree.gameplay.gamemodes.instactf.getChild("test");
		if (testNode.get() == "a") {
			testNode.set("b");
		} else if (testNode.get() == "b") {
			testNode.set("c");
		} else if (testNode.get() == "c") {
			testNode.set("a");
		}
		if (tree.debug) {
			console.log(tree.toJson());
		}
	}
	setInterval(rotateTestNode, 5 * 1000);
	*/
	var debugTree = function() {
		if (tree.debug) {
			console.log(tree.toJson());
		}
	}
	setInterval(debugTree, 5 * 1000);

}

module.exports = TreeTest;

