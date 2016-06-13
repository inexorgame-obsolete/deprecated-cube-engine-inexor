var Tree = require('../app/tree'); // Core library
var expect = require('chai').expect;

describe('Tree', function() {
    describe('datatype', function() {
        it('Should be true that a Node is of datatype tree', function() {
            let node = new Tree.Node(null, "", "node"); // Root node
            expect(node).to.satisfy(Tree.util.isValidDataType); // I don't know what's wrong here?
        });
    });
});