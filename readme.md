# Inexor

Inexor is a fork of the quake-like fps Cube 2: Sauerbraten. It is backwards compatible to the current Cube 2: Sauerbraten release.

## Game Features

* see wiki for actual list of game features

### Engine Features

* see wiki for actual list of engine features

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

* [Website](http://inexor.org)
* [Wiki](https://github.com/inexor-game/code/wiki)
* [Issue Tracker](https://github.com/inexor/code/issues)
* [Source Repository](https://github.com/inexor/code)
* [Chat (irc.gamesurge.net #inexor)](irc://irc.gamesurge.net/#inexor)
 * [Webchat](http://webchat.gamesurge.net/?channels=inexor)

## Credits

### Inexor

* see wiki for the actual list of developers and content designers

### Sauerbraten/Cube2

* Wouter "[Aardappel](http://strlen.com/)" van Oortmerssen: A lot of the general code, and the original concept and design. 
* Lee "[eihrul](http://sauerbraten.org/lee/)" Salzman: ENet networking library, nix ports, and a lot of the general code, especially rendering/lightmaps/physics related. 
* Mike "Gilt" Dysart: General programming, especially editing/physics related.
* Robert "[baby-rabbit](http://www.fernlightning.com/)" Pointon: GUI, particle rendering, and movie recording code, MacOSX porting. 
* Quinton "[quin](http://www.redeclipse.net/)" Reeves: Bots/AI code. Asissts with community management, documentation/wiki, and development. 

with contributions from:

* Adrian "driAn" Henke: MD3 code.
* Jerry Siebe: Geometry rendering optimisations.


### Other

* The [SDL team](http://www.libsdl.org/): For their libraries.

## Copyright

The Inexor source code, the Cube 2: Sauerbraten source code, 
and Inexor files are provided under the terms of the
ZLIB license:

http://www.opensource.org/licenses/zlib-license.php
(very similar to the BSD license):

### Notes

The license covers the source code found in the "src"
directory of this archive (or the source repository on GitHub) as well as the .cfg files under
the "data" directory (or the data repository on GitHub). The included ENet network library which
Inexor uses is covered by an MIT-style license,
which is however compatible with the above license for all
practical purposes.

Game media included in the game (maps, textures, sounds,
models etc.) are NOT covered by this license, and may have
individual copyrights and distribution restrictions (see
individual readmes).

### Inexor

Inexor.

Copyright (C) 2011-2014 **TODO**

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

### Cube 2: Sauerbraten

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

### Logo
The following Logo is the provisional logo. It is more or less based on the original logo and simplified.

![Logo](https://avatars1.githubusercontent.com/u/5883878?v=2&s=420)
