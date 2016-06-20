## Changelog

### Steroids Alpha Edition (v0.8.0-alpha, 2016-06-21)

#### Code internals, refactoring & bug fixes
  * Windows: Update to Node.js v6.2.1 + npm v3.9.3 (#301)
    * this fixes the path too long problem (#297)
  * Windows: Enforce usage of our shipped versions of Node.js, npm and git (no system installed versions) (#301)
  * new RPC; syncing Node.js tree (#311)


***


### Sultiame Alpha Edition (v0.7.0-alpha, 2016-04-25)

#### Server
  * added support for persistent teams (toggleable)
  * added personal messages via the command `pm <cn> <text>`
  * added followfov setting: allows you to automatically adapt to the fov of the player you are spectating
  * added possibility to set a tag (for e.g. a clan): if the whole team shares the same tag, the tag will be shown instead of the default team name

#### UI
  * extended scoreboard: show flags (`/showflags 1`), frags (`/showfrags 1`) and accuracy (`/showaccuracy 1`)
  
#### Code internals, refactoring & bug fixes
  * many improvements concering textures and CMake
  * added new logging library


***


### Doxylamine Alpha Edition (v0.6.0-alpha, 2016-03-06)

#### Graphics
  * ambient occlusion shadows are now antialiased
  * ambient occlusion is now opt-in for new maps
  * further minor ambient occlusions improvements and fixes
  
#### Server
  * readded the old master server with small adjustments as a temporary solution
  * added command `mapmode <map> <mode>` (standalone servers only)
  * added command line option `-x` to use another config file as `server-init.cfg`
  * spectate players with modified map (you can disable this with `spectatemodifiedmap 0`)

#### Node.js / CEF
  * Node.js is getting started automatically with Inexor now
  * started to add a new implementation of a web server + UI
  
#### Code internals, refactoring & bug fixes
  * fixed a crash when a vslot has an invalid texture definition


***


### Tilidine Alpha Edition (v0.5.0-alpha, 2016-01-04)

#### Content management
  * auto detection of multiple data repositories
  * directory restructuring

#### UI
  * fixed bot inserting via menu, always display bot menu

#### Code internals, refactoring & bug fixes
  * added support for GCC 5.3
  * changed the source code directory structure
  * added contributing.md guidelines
  * the subsystem implementation is now memory safe 
  * reintroduced a stackwalker for release binaries
  * merged all Sauerbraten improvements till SVN r5238
  * fixed: pressing the button to open the chat console also prints the key in the chat console
  * fixed: double console input while running CEF


***


### Pyrimethamine Alpha Edition (v0.4.0-alpha, 2015-11-01)

#### Content management
  * various license and readme updates and clarifications
  * improve chainsaw sounds further
  * data-additional changes:
    * added map Haze

#### UI
  * console autocomplete SHIFT-TAB to cycle backwards
  * added prefab UI for easy pasting + autocomplete for prefabs
  * sounds: don't interrupt song on map change, return again to intro song on disconnect, don't output that a song is getting played when it's muted
  
#### Code internals, refactoring & bug fixes
  * replace Sauerbratens's own RNG with the C++11 libs
  * linux: Work around libudev naming issues
  * fixed: screenshotdir gets ignored if you don't specify screenshot name
  * updating our Travis CI environment from Ubuntu 12.04 to Ubuntu 14.04 as well as speeding up the whole process
  * adding support for Microsoft Visual Studio 2015, dropping support for 2013 (only affects prebuilt dependencies)
  
#### Updates
##### 0.4.1 - 2015-11-19
  * improved: don't try to load missing map models on each frame
  * fixed: crash on explosions 
  * fixed: crash when starting subsystems in startup scripts
  * fixed: /getmap tries to load non-existing local map
  * fixed: /resetgl tries to load non-existing files
  * fixed: loading CEF resources + installing the CEF locales


***


### Aquarust Alpha Edition (v0.3.0-alpha, 2015-09-06)

#### Content management

 * added debris and gibs mdls (fixes FPS drop on explosions)
 * fixed sound errors
 * fixed IronSnout's rifle hudgun
 * fixed F3 edit binding
 * added intro/menu song
 * added 5 new crosshairs
 * added 2 hardcoded test servers
 * added new chainsaw sounds
 * maps: new map Legacy, updated Cartel and Pandora
 * introduction of additional data: this data provides more content for our testers and will be removed when we adding an ingame content downloader
 * data-additional changes:
   * maps: added Laucin, Inexor, Star and Averas

#### Gameplay

 * enable the HUD again
 * fixed waypoint loading
 * new default screenshot filename, including the full date
 * display which music is getting played
 
#### Node.js / CEF

 * added (temporary) startscript for Windows
 * provide an own window manager
 * restructuring of large portions of the node code 

#### Code internals & refactoring
 * minor improvements in the loading of sounds and textures
 * multiplayer undo and vslots changes
 * removed everything but the shader rendering pipeline.
 * align the Sauerbraten base to tesseract
 * tests are running now on Appveyor (Windows) and on Travis (Linux)
 * added framework for throwing events when a variable is changed
 * changed default game ports: the new server port is 31415, the new master port 31416


***


### Ritalin Edition (v0.2.0-alpha, 2015-07-12)

#### Content management

* Added more open source textures and sounds
* Improvements on existing maps

#### Gameplay

* Allow zoomfov up to 150
* Spectators can fly around in intermission

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

#### Code internals & refactoring

* Fully modular and dependency based build system
* Progressing modularization of the source code (defined concept of subsystems which can be turned on and off again)
* Rename `src/` to `inexor/` to avoid collisions with system libraries, also namespaces and includes fit better together
* Use AppVeyor for continuous testing on Windows
* Fixed a use-after-free in the exception management code (InexorException)
* Fixed a rare memory leak in the RPC code
* Fixed a frequent memory leak in MessageConnect


***


### Caffeine Edition (v0.1.0-alpha, 2015-05-01)

* Choosed the name of the game

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
 
#### Graphics

* Implemented ambient occlusion during the calclight process (zero cost ingame, calculated during calclight)

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

#### Inter Process Communication

* Communication with the Inexor process
* External NodeJS integration
