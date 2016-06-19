# Inexor Tree API Gluecode Generator

This is the gluecode generator for the [ Inexor Tree API ]( https://github.com/inexor-game/code/wiki/Inexor-Tree-API ).

It parses the source files you hand it and generates the protobuf protocol file (used for networking)
and the c++ rpc handling code based on some template files.
Therefore we use the mustache template engine to render the files and libclangtooling to parse the sourcecode
and find the interesting information in the AST.

In the future it should be expanded to also contain functions, data structures (like vectors) and classes.  
Furthermore a better C++ API should be added to specify neatly the information about the shared vars/.. in the code.  
I.e. `VARP(fullscreen, 0, 1, 2);` could be transformed to sth like `SHARED(fullscreen, Range(0, 2)|Default(1))` 
to simplify extending it for different purposes (e.g. gameservers based on the tree).


The gluecode generator uses libclang with clang's libtooling to generate a standalone analyzer.
In the future it could be possible to run this as a clang
plugin in order to avoid the additional compilation step.

## Building

To build the gluecode generator you need to enable the target `BUILD_GLUEGEN` (and should probably disable any other target) while cmaking.
Then just make install as usual.

## Invocation

The gluegen tool gets executed automatically before any complete rebuild, outputting the gluecode files.
