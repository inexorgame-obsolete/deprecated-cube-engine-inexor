## Changelog

### Speed Release (0.9.0@beta, 2017-11-12)

#### Social

  * Organized a hackathon in Tübingen (Germany)
  * Using riot as main developer and support channel (https://riot.im/app/#/room/#inexor:matrix.org)
  * Added a public telegram group at https://t.me/inexor

#### User Interface / Web Technologies

  * Migrating from Cubescript UI to HTML5/CSS/JS
      * First draft of a HUD using HTML5, JS and websockets
  * Created a new framework for running multiple interfaces at the same time
      * The interfaces are provided by Inexor Flex
      * Fetching interfaces from remote GIT
      * Rendering multiple user interfaces in Inexor Core via CEF
  * Improvements for chromium embedded framework (CEF)
      * new command `/new_ui 1` to test the new interfaces
          * `/showhudlayer 1`
          * `/showapplayer 1`
          * `/showconsolelayer 1`
      * Use CEF in multi-process mode making it much more performant
      * First draft of routing inputs (mouse, keypress) to the target user interface
      * Fixed various bugs
  * Added an user interface for Inexor Flex for managing profiles, instances, media repositories, releases and logging

#### Media Repositories

  * Introduced a framework for the management of multiple media repositories from several sources
  * Fetching and updating media repositories from remote GIT

#### Flexibilization ( / Engine Refactoring)

  * Introduction of **Inexor Flex** as scripting and management enviroment for a single or even multiple instances of Inexor Core
  * Added a **RESTful API** for full access to Inexor Flex and therefore to the instances tree(s)
      * This enables you to script your server using external programs
      * Added the Inexor Tree Client library in order to ease the usage of the Inexor Flex RESTfull API

  * Introduced a **Command Line API** for Inexor Flex `node inexor.js <cmd>` with extensive help
  * Introduced the **Inexor Shell** which uses the command line API

  * InexorGlueGen: Rewritten RPC interface between Inexor Core and Inexor Flex
      * C++ Nodejs bindings API
      * Complete rewrite of the reflection tool
      * Move from libclang to doxygen parsing
      * Expose all CubeScript Vars to the InexorTree
      * Made the **Inexor Tree** available via websockets as well
  * Using standard paths for better cross platform compatibility
      * defines storage location of configurations and data
      * also first preparation for MacOSX support
  * Using TOML as general configuaration file format
      * human readable
      * machine processable
      * comments possible

#### InexorFlex manages InexorCore

InexorFlex is the node.js part.
InexorCore is what one would have called Inexor/Sauerbraten before (the C++ part).

  * Instances Framework
     * Moving  configuration Loading from Inexor Core to Inexor Flex side needed startup changes
         * First start Inexor Flex, then Inexor Core.
     * Manage and run multiple instances of Inexor Core
          * Configure instances using configuration files
          * Start instances of Inexor Core automatically

  * Profiles
      * Like Mozilla Firefox profiles
          * different settings for different profiles
      * Predefined configuration setups
          * client, server, serverfarm and development environments
      * Multiple InexorFlex on the same machine

  * Removed all git submodules
      * Replaced with InexorFlex auto update functionality

#### Build

  * Using a dependency management system for C++
      * conan.io
      * Moved all C++ dependencies to conan.io
      * Wrote packages for all dependencies which weren't supported by conan.io
      * Linux portability including the support of static linking for most dependencies (except SDL (using gcc) and CEF)
  * Added support for more compiler / IDE enviroments:
      * gcc 7.x
      * Visual Studio 2017
  * Added Continous Deployment (CD) machinery
      * Every commit (branch or pull request) is build by Travis (Linux) and AppVeyor (Windows)
      * Ensure commit message quality using gitcop
      * Ensure code quality using [eslint](eslint.org)
      * Check for security issues using [nsp](nodesecurity.io)
      * Every pushed commit to master is a new release (rolling release)

#### Release Mangement

  * Distribution
      * Added Windows installer
      * Added Snap package (Linux)
      * Made Inexor Flex installable via `npm install @inexorgame/inexor-flex`
  * Inexor Core, Inexor Flex, media repositories and user interfaces are coupled loosely and released separately
  * Rolling Release
      * New alpha releases get created automatically on each push to the master branch of Inexor Core
      * Releases get build in the CI & uploaded to GitHub
  * InexorFlex downloads releases
      * received from Inexors-GitHub or any other provider
          * support for REST and filesystem providers
          * releases.toml specifies providers
          * instances.toml specifies used release
      * or build locally
  * Changed Versioning to add a channel
      * version@channel
      * channel *alpha* gets published on each push to master
      * channel *beta* gets published manually by the dev team
  * Unified names of the executables of Inexor Core #430

#### C++ Refactoring

  * Consequent usage of the new logging framework in Inexor Core
  * Reformatted log messages in Inexor Core
  * Logging Framework for Inexor Flex
      * Integration of Inexor Core logging
  * Pragma once instead of include guards #489

#### Website

  * New design
  * Show blog posts
  * Better navigation
  * Download Page
  * Improved code structure


***


### Steroids Alpha Edition (0.8.0-alpha, 2016-06-21)

#### Code internals, refactoring & bug fixes
  * Windows: Update to Node.js v6.2.1 + npm v3.9.3 (#301)
    * this fixes the path too long problem (#297)
  * Windows: Enforce usage of our shipped versions of Node.js, npm and git (no system installed versions) (#301)
  * new RPC; syncing Node.js tree (#311)


***


### Sultiame Alpha Edition (0.7.0-alpha, 2016-04-25)

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


### Doxylamine Alpha Edition (0.6.0-alpha, 2016-03-06)

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


### Tilidine Alpha Edition (0.5.0-alpha, 2016-01-04)

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


### Pyrimethamine Alpha Edition (0.4.0-alpha, 2015-11-01)

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


### Aquarust Alpha Edition (0.3.0-alpha, 2015-09-06)

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


### Ritalin Edition (0.2.0-alpha, 2015-07-12)

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


### Caffeine Edition (0.1.0-alpha, 2015-05-01)

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
