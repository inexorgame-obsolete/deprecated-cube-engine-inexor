/**
 * Fake inexor object if not available (i.e. not started by inexor)
 */
if (!inexor || !inexor.console) {
	var inexor = {console:{},event:{}};
	inexor.event.subscribe = function() {}
	inexor.console.log = function() {}
}

var consoleOut = null;
var consoleIn = null;
var consoleInputField = null;

var getKeyCode = function(e) {
    if (!e) e = window.event;
    return e.keyCode || e.which;
};

/**
 * If true, the console is in expanded state, else in shrinked state.
 */
inexor.console.expanded = false;

/**
 * If true, the console is tailing the console output.
 */
inexor.console.follow = false;

/**
 * If true, the console debug is enabled.
 */
inexor.console.debug = false;

/**
 * Redirect the native browser console, print in output window and
 * redirect back into the native browser console.
 */
inexor.console.jslog = console.log.bind(console);
inexor.console.out = function(string) {
    var output = document.getElementById('consoleout-data');
    var html = output.innerHTML + '<br />' + string;
    output.innerHTML = html;
    consoleOut.scrollTop = consoleOut.scrollHeight;
	inexor.console.log(string);
	inexor.console.jslog(string);
};
console.log = inexor.console.out;

/**
 * Execute JS code.
 */
inexor.console.eval = function(code) {
	inexor.console.jslog("Eval: " + code);
	eval(code);
};

/**
 * Switch to expanded state.
 */
inexor.console.expand = function() {
	inexor.console.expanded = true;
	consoleOut.className = 'consoleout active';
	consoleIn.className = 'consolein active';
	consoleInputField.focus();
	consoleInputField.onkeyup = function(e) {
		if (getKeyCode(e) == '13') {
			inexor.console.eval(consoleInputField.value);
			return false;
		}
	};
};

/**
 * Switch to shrinked state.
 */
inexor.console.shrink = function() {
    inexor.console.expanded = false;
    consoleOut.className = 'consoleout inactive';
    consoleIn.className = 'consolein inactive';
    consoleInputField.blur();
    delete consoleInputField.onkeypress;
};


/**
 * Toggles expanded and shrinked state.
 */
inexor.console.toggle = function() {
	if (inexor.console.expanded) {
		inexor.console.shrink();
	} else {
		inexor.console.expand();
	}
};

/**
 * Follow the last output lines. Automatically unfollow and
 * follow again if the user has used the scrollbars.
 */
inexor.console.tail = function() {
	var diff = consoleOut.scrollHeight - (consoleOut.scrollTop + consoleOut.offsetHeight);
	if (inexor.console.follow) {
		// TODO: make scrollheight diff configurable
		if (diff > 50) {
			inexor.console.follow = false;
		} else {
		    consoleOut.scrollTop = consoleOut.scrollHeight;
		}
	} else {
		// TODO: make scrollheight diff configurable
		if (diff < 50) {
			inexor.console.follow = true;
		}
	}
	// TODO: make tail interval configurable
    window.setTimeout(inexor.console.tail, 100);
};

/**
 * Console initialization.
 */
inexor.console.init = function() {
    consoleOut = document.getElementById('consoleout');
    consoleIn = document.getElementById('consolein');
    consoleInputField = document.getElementById('consolein-field');
    inexor.console.out("Console Initialized!");
    inexor.console.tail();

    // Bind keys
    Mousetrap.bind('esc', inexor.menu.toggle);
    Mousetrap.bind('f11', inexor.console.toggle);
    Mousetrap.bind('f10', inexor.debug.toggle);
};
window.setTimeout(inexor.console.init, 100);

/**
 * Bind ESC on toggle console.
 */
/*
window.onkeydown = function(e) {
    if (getKeyCode(e) == '27') {
        inexor.console.toggle();
        return false;
    }
};
*/

/**
 * Subscribe events.
 */
inexor.event.subscribe("frag", function(victim, actor) {
	inexor.console.out(inexor.game.getClientName(actor) + " fragged " + inexor.game.getClientName(victim));
});
inexor.event.subscribe("connect", function(cn, name) {
	inexor.console.out("connect: " + name + "(" + cn + ")");
});
inexor.event.subscribe("disconnect", function(cn, name) {
	inexor.console.out("leave: " + name + "(" + cn + ")");
});
inexor.event.subscribe("rename", function(cn, oldName, newName) {
	inexor.console.out(oldName + " is now known as " + newName);
});


/** Some Debug Stuff **/
