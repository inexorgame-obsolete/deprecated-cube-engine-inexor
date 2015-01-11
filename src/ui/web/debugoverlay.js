
var getKeyCode = function(e) {
    if (!e) e = window.event;
    return e.keyCode || e.which;
};


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

function debugKeyEvent(t, e) {
    if (!e) e = window.event;
   	document.getElementById('keys-' + t + '-keycode').value = e.keyCode;
   	document.getElementById('keys-' + t + '-charcode').value = e.charCode;
   	document.getElementById('keys-' + t + '-which').value = e.which;
	if (inexor.console.debug) {
	   	inexor.console.out(t + "," + e.keyCode + "," + e.charCode + "," + e.which);
	}
};

/**
 * Bind ESC on toggle console.
 */
window.onkeydown = function(e) {
	debugKeyEvent("onkeydown", e);
};
window.onkeypress = function(e) {
	debugKeyEvent("onkeypress", e);
};
window.onkeyup = function(e) {
	debugKeyEvent("onkeyup", e);
};
