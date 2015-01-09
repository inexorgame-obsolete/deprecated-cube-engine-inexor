/**
 * True, if the console is expanded.
 * @param string
 */
if (!inexor || !inexor.console) {
	var inexor = {console:{},event:{}};
	inexor.event.subscribe = function() {}
	inexor.console.log = function() {}
}

inexor.console.expanded = false;

inexor.console.jslog = console.log.bind(console);

inexor.console.out = function(string) {
    var output = document.getElementById('consoleout-data');
    var html = output.innerHTML + '<br />' + string;
    output.innerHTML = html;
	inexor.console.log(string);
	inexor.console.jslog(string);
}

console.log = inexor.console.out;

inexor.console.eval = function(code) {
	inexor.console.jslog("Eval: " + code);
	eval(code);
}

inexor.console.expand = function() {
	inexor.console.expanded = true;
	var consoleOut = document.getElementById('consoleout');
	var consoleIn = document.getElementById('consolein');
	var consoleInputField = document.getElementById('consolein-field');
	consoleOut.className = 'consoleout active';
	consoleIn.className = 'consolein active';
	consoleInputField.focus();
	consoleIn.onkeypress = function(e) {
		if (!e) e = window.event;
		var keyCode = e.keyCode || e.which;
		if (keyCode == '13') {
			inexor.console.eval(consoleInputField.value);
			return false;
		}
	};
}

inexor.console.shrink = function() {
	inexor.console.expanded = false;
	var consoleOut = document.getElementById('consoleout');
	var consoleIn = document.getElementById('consolein');
	var consoleInputField = document.getElementById('consolein-field');
	
	consoleOut.className = 'consoleout';
	consoleIn.className = 'consolein';
	consoleInputField.blur();
	delete consoleIn.onkeypress;
}

inexor.console.toggle = function() {
	if (inexor.console.expanded) {
		inexor.console.shrink();
	} else {
		inexor.console.expand();
	}
}



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

inexor.event.subscribe("frag", function(victim, actor) {
	inexor.console.out(victim + " fragged " + actor);
});

window.setTimeout(function() {
	inexor.console.out("Console Initialized!");
	inexor.console.expand();
}, 3000);
