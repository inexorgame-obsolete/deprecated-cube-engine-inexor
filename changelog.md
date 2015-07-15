## Changelog

### Ritalin Edition (v0.2.0-alpha, 2015-07-12)

#### Code internals & Refactoring

* Fully modular and dependency based build system
* Progressing modularization of the source code (defined concept of subsystems which can be turned on and off again)
* Rename `src/` to `inexor/` to avoid collisions with system libraries, also namespaces and includes fit better together
* Use AppVeyor for continuous testing on Windows
* Fixed a use-after-free in the exception management code (InexorException)
* Fixed a rare memory leak in the RPC code
* Fixed a frequent memory leak in MessageConnect

#### CEF
* Integration of CEF (not yet enabled via default)
* CEF UI Framework
 * Basic working framework that will be used to render HTML5 UIs with node.js and CEF
   * Dependency management with node modules, requires and angular
   * Node modules are available in the browser with a Browserify/RequireJS bridge (so we do not have to dump external libraries into our repo)
   * Uses express.js in the server
   * Uses jQuery
   * Uses lodash
   * Uses Bootstrap
   * Uses Angular.js
   * Supports CoffeeScript
   * Supports Jade
   * Supports Stylus
   * Create angular directives as CoffeeScript classes, with automatically loaded CSS (Stylus) and HTML (Jade) files
   * Window management

#### Content management

* Added more open source textures and sounds
* Improvements on existing maps

#### Gameplay

* Allow zoomfov up to 150
* Spectators can fly around in intermission


***


### Caffeine Edition (v0.1.0-alpha, 2015-05-01)

* Choosed the name of the game

#### Develoment environment

* GitHub source code, issues, wiki
* Travis build server
 * Nightly builds for testing
* Waffle.io kanboard
* Separate repositories for code and content

#### More flexible build system

* CMake setup (unified cross platform build environment)
* New file structure for generated binaries
* Separated external libraries from our source (including ENet)

#### Refactoring and code cleanup

* Remove static file paths
* Remove rpggame
* Remove Cube 1 map loader
* Cleaner data/media structure

#### Integration of 3rd party libraries

* SDL2 (including better fullscreen support under Linux)
* Muparser (math expression library)
* JSON API
* JSON Import API (not completed yet)
 * JSON references to other JSON files

#### Unit tests

* Integrated unit test framework: Google Test

#### API documentation

* Defined a standardized way of documenting packages and their content
* Documentation guidelines
* Integrated Doxygen

#### Licensing and content management

* Choose legitimate licenses to use for content ("License Policy")
* Provide some freely licensed basic textures and maps

#### Gameplay

* Renamed /kill to /suicide
* Console improvements
 * Warnings won't spam the console anymore
 * Lines are fading out, instead of simple disappear
 * Timestamps
 * History, reuse commands easily from your last game session

#### Inter Process Communication

* Communication with the Inexor process
* External NodeJS integration

#### Graphics

* Implemented ambient occlusion during the calclight process (zero cost ingame, calculated during calclight)
