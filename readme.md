# Inexor

[![Build Status](https://ci.inexor.org/job/code/badge/icon)](https://ci.inexor.org/job/code/) [![Build Status](https://travis-ci.org/inexor-game/code.svg?branch=master)](https://travis-ci.org/inexor-game/code) [![Build status](https://ci.appveyor.com/api/projects/status/h9kwt5lk54epjv8t/branch/master?svg=true)](https://ci.appveyor.com/project/inexor-game/code)

Inexor is a fork of the open-source First-Person-Shooter Cube 2: Sauerbraten, a fast-paced shooting game featuring an ingame map editor.  
In contrast to Sauerbraten, Inexor adds a lot of functionality and strives to stay open to improvements and suggestions.  
The goal of this project is to be more flexible and create an environment where development is easy, fast and where creativity can prosper.


## How is Inexor organized?

We are a non-hierarchical organisation. This means we are simply a group of people with different ideas working together without a leader making all the decisions. Anyone of us is free to work on the particular things they want to.
For this organisation to work properly we rely on good communication. We are on IRC and Mumble pretty much everyday. Every so often we organise official Mumble meetings to discuss our roadmap and strategies.

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

However, if you want to influence our development you should join our IRC-channel #inexor on gamesurge.net (see [Contact](https://github.com/inexor-game/code/wiki/Contact)) and talk with us.  

And of course we won't be too proud to rethink this list if you face us with a more thought-through and better developed alternative.


## What have we changed already?

Have a look in our [features section](https://github.com/inexor-game/code/wiki#features) and our 
[changelog](https://github.com/inexor-game/code/blob/master/changelog.md).


If you are a developer familiar with Sauerbraten worrying about the direction we are going check out the posts in our blog called
"Design Decisions" ([Design-Decisions Part1](https://inexor.org/blog/2015/04-26-alpha1-design-decisions), [Design-Decisions Part2](https://pad.inexor.org/p/Alpha3_Design_Decisions)) giving you a vague idea of our reasoning for some points.  
You'll probably find more info on the dedicated wiki-sites, in the readme of the particular module and for specific stuff in the [documentation](https://docs.inexor.org).


A little note on that is that a lot of our decisions are consequences of other ones (e.g. working as a team had influences on the whole build structure, that we use CMake, that we use Git and hence had to split the data and code repository and more ...  it's all chained).
Consequently, our approach in developing Inexor is probably the most profound one in the Cube engine world.


## Build

Good tutorials on the whole process needed to build Inexor can be found in its [wiki page](https://github.com/inexor-game/code/wiki/Build), which you should read beforehand for saving you some nerves.


## Join us

You have already accomplished the first step by reading this readme. Congratz!

The second one is only slightly harder by joining us in IRC (again see the wiki site for that: [Contact](https://github.com/inexor-game/code/wiki/Contact)) and idling/participating in our chat.

To contribute to the project and merge your changes into the master branch you need to convince enough members that the changes are an improvement.
If you keep communicating what you are doing, take into account feedback and tips from others as well as giving insights into your decision making process, it won't be an issue.

More information about the contributing process can be found [here](https://github.com/inexor-game/code/wiki/How-To-Contribute-Code).


## Resources

* [Website](https://inexor.org)
* [Wiki](https://github.com/inexor-game/code/wiki)
* [Issue Tracker](https://github.com/inexor-game/code/issues)
* [Kanboard](https://waffle.io/inexor-game/code)
* [Documentation](https://docs.inexor.org)
* [Source Repository](https://github.com/inexor-game/code)
* [Data Repository](https://github.com/inexor-game/data)
* [IRC Chat (irc.gamesurge.net #inexor)](irc://irc.gamesurge.net/#inexor)
 * [Webchat](https://webchat.gamesurge.net/?channels=inexor)

