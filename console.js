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
		if (diff > 50) {
			inexor.console.follow = false;
		} else {
		    consoleOut.scrollTop = consoleOut.scrollHeight;
		}
	} else {
		if (diff < 50) {
			inexor.console.follow = true;
		}
	}
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
};
window.setTimeout(function() {
    inexor.console.init();
}, 100);

var debugKeyEvent = function(t, e) {
    if (!e) e = window.event;
   	document.getElementById('keys-' + t + '-keycode').value = e.keyCode;
   	document.getElementById('keys-' + t + '-charcode').value = e.charCode;
   	document.getElementById('keys-' + t + '-which').value = e.which;
   	inexor.console.out(t + "," + e.keyCode + "," + e.charCode + "," + e.which);
};

/**
 * Bind ESC on toggle console.
 */
window.onkeydown = function(e) {
	debugKeyEvent("onkeydown", e);
// window.onkeypress = function(e) {
    if (getKeyCode(e) == '27') {
        inexor.console.toggle();
        return false;
    }
};
window.onkeypress = function(e) {
	debugKeyEvent("onkeypress", e);
};
window.onkeyup = function(e) {
	debugKeyEvent("onkeyup", e);
};

/**
 * Subscribe events.
 */
inexor.event.subscribe("frag", function(victim, actor) {
	inexor.console.out(actor + " fragged " + victim);
});


/** Some Debug Stuff **/


function check() {
    if(typeof inexor == 'object') inexor.console.out('inexor == object');
    if(typeof inexor.layer == 'object') inexor.console.out('inexor.layer == object');
    if(typeof inexor.layer.show == 'function') inexor.console.out('inexor.layer.show == function');
    if(typeof inexor.layer.hide == 'function') inexor.console.out('inexor.layer.hide == function');
    if(typeof inexor.event == 'object') inexor.console.out('inexor.event == object');
    if(typeof inexor.event.subscribe == 'function') inexor.console.out('inexor.event.subscribe == function');
    if(typeof inexor.event.fire == 'function') inexor.console.out('inexor.event.fire == function');
    if(typeof inexor.menu == 'object') inexor.console.out('inexor.menu == object');
    if(typeof inexor.console == 'object') inexor.console.out('inexor.console == object');
}

function printInexor() {
	inexor.console.out(JSON.stringify(inexor, undefined, 2));
}

function printEvents() {
	inexor.console.out(JSON.stringify(inexor.event.list(), undefined, 2));
}
