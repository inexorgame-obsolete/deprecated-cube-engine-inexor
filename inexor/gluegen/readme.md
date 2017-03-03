# InexorGlueGen
## Inexor Tree API Gluecode Generator

This is the gluecode generator for the [ Inexor Tree ]( https://github.com/inexor-game/code/wiki/Inexor-Tree)(currently used for our scripting API).

It parses the C++ source files you hand it and generates the protobuf protocol file 
and the C++ handling code based on some template files.
Therefore we use the mustache template engine to render the files and doxygen to parse the sourcecode.

You can find examples of its usage in the wiki.

## Building

InexorGluegen gets usually only build once. As its a build-tool we need to have it be built before actually building Inexor and even before generating Inexors makefiles/project files. 
So we make it a self-contained conan.io-package (Conan is our package manager) which gets created (`conan export`ed) as a step of `conan install` for Inexor. This is a bit of a hack.
As Conan caches all builds you have two options to make changes to the InexorGlueGen-Code and see them in action:

1. Increment InexorGlueGen's version
    * Two places: the conanfile in inexor/gluegen/ and the main one (main folder) which references it.
2. Use the `DEBUG_GLUEGEN`-flag of CMake
    * (pass -DDEBUG_GLUEGEN=1)
    * This is recommended
        * since you do not need to increment all the time again


To run the InexorGlueGen binary for testing purposes you still need to pass it the arguments it needs for doing its job.
As you do not want to search for it (or hack it together from the source) you can grab the list from the output of running CMake for generating the Inexor build files.

## Invocation

The gluegen tool gets executed automatically on the first build (or if you removed your build-folder).
To trigger a regeneration of the API you can manually build the target `regenerate-gluecode-inexor` (or `regenerate-gluecode-server`).


## TODO

* Mustache templates are very unreadable, if there is a better alternative: switch.
* Add an UPDATE-mechanism
    * only updating the protobuf file, not completely renewing it

