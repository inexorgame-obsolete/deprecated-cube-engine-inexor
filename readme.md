# Sauerbomber

Sauerbomber is a fork of the quake-like fps Sauerbraten/Cube2, that adapts the Bomberman game for an FPS environment.
It is compatible to the current Sauerbraten/Cube 2 release.

## Features

* Bomberman mode
* Last Man Standing mode
* Race mode
* Hide and Seek mode

### Engine Features

* Destructable Map models
* Localized Force Fields

### Sauerbraten Features

* Oldskool fast & intense gameplay (read: similar to Doom 2 / Quake 1).
* Many multiplayer gameplay modes, most in teamplay variants as well: deathmatch, instagib, efficiency, tactics, capture (domination/battlefield style), CTF (capture the flag), coop edit (!).
* 7 weapons: double barrelled shogun, rocket launcher, machine gun, rifle, grenade launcher, pistol, fist.

### Cube 2 Engine Features

* 6 directional heightfield in octree world structure allowing for instant easy in-game geometry editing (even in multiplayer, coop edit).
* Rendering engine optimized for high geometry throughput, supporting hardware occlusion culling and software precomputed conservative PVS with occluder fusion.
* Lightmap based lighting with accurate shadows from everything including mapmodels, smooth lighting for faceted geometry, and fast compiles. Soft shadowmap based shadows for dynamic entities.
* Pixel and vertex shader support, each model and world texture can have its own shader assigned. Supports normal and parallax mapping, specular and dynamic lighting with bloom and glow, environment-mapped and planar reflections/refractions, and post-process effects.
* Loading of md2/md3/md5/obj/smd/iqm models for skeletal and vertex animated characters, weapons, items, and world objects. Supports animation blending, procedural pitch animation, and ragdoll physics for skeletally-animated characters.
* Simple stereo positional sound system.
* Particle engine, supporting text particles, volumetric explosions, soft particles, and decals.
* 3d menu/gui system, for in-world representation of choices.

## Resources

* [Web site, well probably somewhen](http://sauerbomber.org)
* [Wiki](http://forge.nooblounge.net/projects/bomberman/wiki)
* [Issue Tracker](http://forge.nooblounge.net/projects/bomberman/issues)
* [Source Repository](https://github.com/mobius-tempname/sauerbomber)
* [Chat (irc.nooblounge.net #talk)](irc://irc.nooblounge.net/#talk)
* [Sauerbraten Wiki](http://cube.wikispaces.com/)
* [Sauerbraten Docs](http://sauerbraten.org/README.html)

## Credits

### Sauerbomber

* Karolin "mapc" Varner
* Andreas "hanack" Schaeffer

with

* nothing
* westernheld
* *and many others!*

### Sauerbraten/Cube2

* Wouter "Aardappel" van Oortmerssen: A lot of the general code, and the original concept and design. (website)
* Lee "eihrul" Salzman: ENet networking library, nix ports, and a lot of the general code, especially rendering/lightmaps/physics related. (website)
* Mike "Gilt" Dysart: General programming, especially editing/physics related.
* Robert "baby-rabbit" Pointon: GUI, particle rendering, and movie recording code, MacOSX porting. (website)
* Quinton "quin" Reeves: Bots/AI code. Asissts with community management, documentation/wiki, and development. (website)

with contributions from:

* Adrian "driAn" Henke: MD3 code.
* Jerry Siebe: Geometry rendering optimisations.

### Level Design

* Kurt "kdoom" Kessler: A bunch of DM/capture maps, k_rpg1.
* Shane Nieb: academy, authentic, autumn, bt_falls, c_valley, complex, curvy_castle, flagstone, garden, hallo, hashi, island, justice, nevil_c, nmp4, nmp8, nmp9, ot, park, shipwreck, turbine
* John "metlslime" fitzgibbons: metl maps.
* MitaMan: singleplayer episodes
* With additional maps by: Aardappel, driAn, Gilt, voot, Bryan "KillHour" Shalke, staffy, sparr, JCDPC, ZappaZ, RatBoy, Fanatic, rocknrol, KaiserTodretter, BlikjeBier, wurfel, aftasardem, Lazy [HUN], Gregor Koch, Junebug, Gabriele "Blindabuser" Magurno, MeatROme, TUX, Mayhem, mIscreant, schmutzwurst, Kal, DairyKing, Hero, WahnFred, jonlimle, and others.

### Art / Content

* John "Geartrooper" Siar: Mr. Fixit, Ironsnout, RPG characters, monsters, new hudguns and vweps.
* Gabriele "Blindabuser" Magurno: Logos, loading screen, announcer voices.
* MakkE: Mapmodels, old hudguns, items.
* Dietmar "dcp" Pier: Mapmodels, old hudguns.
* DarthVim: Old hudguns.
* Shane Nieb: Textures, Mapmodels, Skyboxes.
* Sock: The egyptian & tech texture sets (website).
* Iikka "Fingers" Keranen: The ikbase ik2k texture sets (website).
* Lunaran, Gibbie, Gregor Koch, Jésus "aftasardem" Maia, MitaMan, and philipk: Normalmapped texture sets.
* Additional art by: metlslime (textures), Than (textures), Remedy Entertainment Ltd (textures), Seth & Ulrich Galbraith (GPL models), Brian "EvilBastard" Collins, Conrad, Magarnigal, Psionic, James Green, Andreas Möller, Ryan Butts & Jeramy Cooke (md2 models), KaiserTodretter (items), Tentus (mapmodels), Kurt Kessler (mapmodels), Philip Klevestav (textures), leileilol/OpenArena (GPL bullet hole decal).

### Sound / Music

* Marc "Fanatic" A. Pullen: Soundtrack.

### Other

* Kristian "sleepwalkr" Duske: website / messageboard, hosting, master server.
* Pushplay: Documentation help.
* The SDL team: For their libraries (website).

## Copyright

The Sauerbomber source code, the Sauerbraten source code, 
and Sauerbomber files are provided under the terms of the
ZLIB license:

http://www.opensource.org/licenses/zlib-license.php
(very similar to the BSD license):

### Notes

The license covers the source code found in the "src"
directory of this archive as well as the .cfg files under
the "data" directory and content provided by the Sauerbomber
project. The included ENet network library which Sauerbomber
uses is covered by an MIT-style license, which is however
compatible with the above license for all practical
purposes.

Game media included in the game (maps, textures, sounds,
models etc.) are NOT covered by this license, and may have
individual copyrights and distribution restrictions (see
individual readmes).

### Sauerbomber

Sauerbomber/game engine.

Copyright (C) 2011-2014 Karolin Varner, Andreas Schaeffer

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

### Sauerbraten

Sauerbraten game engine source code, any release.

Copyright (C) 2001-2011 Wouter van Oortmerssen, Lee Salzman, Mike Dysart, Robert Pointon, and Quinton Reeves

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
