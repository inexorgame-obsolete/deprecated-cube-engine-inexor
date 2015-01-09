/**
 * True, if the console is expanded.
 * @param string
 */
inexor.console.expanded = false;

inexor.console.expand = function() {
	inexor.console.expanded = true;
	var output = document.getElementById('consoleout').className = 'consoleout-expanded';
}

inexor.console.shrink = function() {
	inexor.console.expanded = false;
	var output = document.getElementById('consoleout').className = 'consoleout-shrinked';
	
}

inexor.console.toggle = function() {
	if (inexor.console.expanded) {
		inexor.console.shrink();
	} else {
		inexor.console.expand();
	}
}

function addOutput(string) {
    var output = document.getElementById('output');
    var html = output.innerHTML + '<br />' + string;
    output.innerHTML = html;
}

function check() {
    if(typeof inexor == 'object') addOutput('inexor == object');
    if(typeof inexor.layer == 'object') addOutput('inexor.layer == object');
    if(typeof inexor.layer.show == 'function') addOutput('inexor.layer.show == function');
    if(typeof inexor.layer.hide == 'function') addOutput('inexor.layer.hide == function');
    if(typeof inexor.event == 'object') addOutput('inexor.event == object');
    if(typeof inexor.menu == 'object') addOutput('inexor.menu == object');
    if(typeof inexor.console == 'object') addOutput('inexor.console == object');
    if(typeof inexor.console == 'object') addOutput('inexor.console == object');
}

function printInexor() {
    addOutput(JSON.stringify(inexor, undefined, 2));
}

function printEvents() {
    addOutput(JSON.stringify(inexor.event.list(), undefined, 2));
}

inexor.event.subscribe("frag", function(victim, actor) {
	addOutput(victim + " fragged " + actor);
});
