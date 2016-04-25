# Inexor

Inexor is a fork of the open-source First-Person-Shooter Cube 2: Sauerbraten, a fast-paced shooting game featuring an ingame map editor.  
In contrast to Sauerbraten, Inexor adds a lot of functionality and strives to stay open to improvements and suggestions.  
The goal of this project is to be more flexible and create an environment where development is easy, fast and where creativity can prosper.

## How is Inexor organized?

We are a non-hierarchical organisation. This means we are simply a group of people with different ideas working together without a leader making all the decisions. Anyone of us is free to work on the particular things they want to.
For this organisation to work properly we rely on good communication. We are on IRC and Mumble pretty much everyday. Every so often we organise official Mumble meetings to discuss our roadmap and strategies.

To contribute to the project and merge your changes into the master branch you need to convince enough members that the changes are an improvement.
If you keep communicating what you are doing, take into account feedback and tips from others as well as giving insights into your decision making process, it won't be an issue.

We are open for new people!

## Where are we headed?

Our goal is to make the game as moddable and developer-friendly as possible.
Even though we might have refactored most of the code at some point, Inexor should always feel like Sauerbraten gameplay wise.

A popular stance among the Sauerbraten community is "that's impossible", and this is what we want to prove wrong. Our answer to remarks like "things are best like they are" is: standing still means falling behind.


##### Different features are afoot 
giving a general but no inevitably defined idea of where we're going next

* node.js scripting
 * (JavaScript + asynchronous + package manager) 
* new user interface using HTML5 + CSS3
* functionality to facilitate content-creating:
  * better editing features (e.g. a version control system for maps)
  * **extensibility** (e.g. for custom playermodels, sounds,..)
* in-game content sharing
* documentiation of the whole code base
* refractored code to be more modern, scaleable, safe, non-blocking, modular, free, ... than before
 * modularity (makes working as/in a team easier)
 * scaleable and non-blocking resulting in better performance
 * heavier use of proven third-party libraries
   * instead of buggy and slow "reinvent-the-wheel" implementations
* ...

We believe that basing our project on these few points will work out for the best.  
They have already required a lot of thought and discussion, so chances are high that -in case you're not fully convinced by them yet- you will get convinced by working with it.

However, if you want to influence our development you should join our IRC-channel #inexor on gamesurge.net (see [Contact](https://github.com/inexor-game/code/wiki/Development-Environment)) and talk with us.  

And of course we won't be too proud to rethink this list if you face us with a more thought-through and better developed alternative.

## What have we changed already?

You can see our changelog [here](https://github.com/inexor-game/code/blob/master/changelog.md).


Furthermore, the [Wiki](https://github.com/inexor-game/code/wiki) has more information.  
If you are a Sauerbraten developer worrying about us changing stuff and we're "totally going in the wrong direction", check out the posts in our blog called
"Design Decisions" ([Design-Decisions Part1](https://inexor.org/blog/2015/04-26-alpha1-design-decisions), [Design-Decisions Part2](https://pad.inexor.org/p/Alpha3_Design_Decisions)) giving you a vague idea of our reasoning for some points.  
(You'll probably find more info on the dedicated wiki-sites, in the readme of the particular module and for specific stuff in the [documentation](http://docs.inexor.org) )


A little note on that is that a lot of our decisions are consequences of other ones (e.g. working as a team had influences on the whole build structure, that we use cmake, that we use git and hence had to split the data and code repository and more ..  it's all chained).
Consequently, our approach in developing Inexor is probably the most profound one in the Cube-world.


# First Steps

You have already accomplished the first step by reading this readme. Congratz!

The second one is only slightly harder by joining us in IRC (again see the wiki site for that: [Contact](https://github.com/inexor-game/code/wiki/Development-Environment)) and idling/participating in our chat.

## Build

Mainly it is:

1. fetching our needed build dependencies (cmake, git)
2. downloading the code and data repository using git
3. creating your specific build-files (makefile/Visual Studio-solution/XCode project/..) using CMake
4. and lastly, building Inexor

Good tutorials on the whole process needed to build Inexor can be found in its [wiki-site](https://github.com/inexor-game/code/wiki/Build), which you should read beforehand for saving you some nerves.


## Resources

* [Website](https://inexor.org)
* [Wiki](https://github.com/inexor-game/code/wiki)
* [Issue Tracker](https://github.com/inexor-game/code/issues)
* [Kanboard](https://waffle.io/inexor-game/code)
* [Source Repository](https://github.com/inexor-game/code)
* [Data Repository](https://github.com/inexor-game/data)
* [Chat (irc.gamesurge.net #inexor)](irc://irc.gamesurge.net/#inexor)
 * [Webchat](https://webchat.gamesurge.net/?channels=inexor)
 
## Game Features

* see wiki for actual list of Inexors features
* Sauerbraten Features

 * Old-school fast & intense gameplay (read: similar to Doom 2 / Quake 1).
 * 23 multiplayer gameplay modes, most in teamplay variants as well: ffa (free for all, deathmatch alike), instagib, efficiency, tactics, capture (domination/battlefield style), CTF (capture the flag), protect (one teammate have to carry the flag), hold (hold a randomly spawning flag for a specific time to score), collect (kill enemies and collect their skulls) and coop edit (create maps together!).
 * 7 weapons: double barrelled shotgun, rocket launcher, machine gun, rifle, grenade launcher, pistol and chainsaw.
 
### Engine Features

* see wiki for actual list of engine features
* Cube 2 Engine Features

 * 6 directional heightfield in octree world structure allowing for instant easy in-game geometry editing (even in multiplayer, coop edit).
 * Rendering engine optimized for high geometry throughput, supporting hardware occlusion culling and software precomputed conservative PVS with occluder fusion.
 * Lightmap based lighting with accurate shadows from everything including mapmodels, smooth lighting for faceted geometry, and fast compiles. Soft shadowmap based shadows for dynamic entities.
 * Pixel and vertex shader support, each model and world texture can have its own shader assigned. Supports normal and parallax mapping, specular and dynamic lighting with bloom and glow, environment-mapped and planar reflections/refractions, and post-process effects.
 * Loading of md2/md3/md5/obj/smd/iqm models for skeletal and vertex animated characters, weapons, items, and world objects. Supports animation blending, procedural pitch animation, and ragdoll physics for skeletally-animated characters.
 * Simple stereo positional sound system.
 * Particle engine, supporting text particles, volumetric explosions, soft particles, and decals.
 * 3d menu/gui system, for in-world representation of choices.
