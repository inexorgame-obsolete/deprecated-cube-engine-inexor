# Inexor Tree API Gluecode Generator

This is a prototypical gluecode generator for the [ Inexor Tree API ]( https://github.com/inexor-game/code/wiki/Inexor-Tree-API ).

At the moment it can list all the SharedVars and their underlying storage types in their canonical forms.
The output should be `(TYPE) VAR_NAME_WITH_NAMESPACe`.

In the future it should be expanded to use this information
to generate protobuf files mirroring that information and to
use those for applying and generating differential state
updates.

Beyond that support for Data Structures needs to be added.

The gluecode generator uses libclang with clang's libtooling to generate a standalone analyzer.
In the future it should be possible to run this as a clang
plugin in order to avoid the additional compilation step.

## Running

You need clang installed and the usual UNIX C programming
tools (e.g. make). And the libraries also used for building
inexor.

Then just invoke:

`make run`
