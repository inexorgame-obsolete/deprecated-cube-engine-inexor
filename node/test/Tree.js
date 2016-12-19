var Tree = require('inexor-tree'); // Core library
var expect = require('chai').expect;

describe('Tree', function() {
    describe('validName', function() {
        it('Should check wether given name is valid', function() {
            let name = "/game/mode"; // @aschaeffer?
            expect(name).to.satisfy(function(name) {
                // See http://stackoverflow.com/a/20579046
                return Tree.util.validName.test.bind(name);
            });
        }); 
    });
    
    describe('datatype', function() {
        it('Should be true that a Node is of datatype tree', function() {
            let node = new Tree.Node(null, "", "node"); // Root node
            expect(node._datatype).to.satisfy(Tree.util.isValidDataType);
        });
    });
});
