# The Texture Loading and Managment Module

### Depends on
cube.h, SDL_image, C++11

### Notes
It can not be used as a "standalone" module.
It does not (yet) use a namespace for the whole module.

## Files and Contents:

* additionaltools.cpp
* additionaltools.h
 Additional (standalone) texture generation tools provided by the engine.

* compressedtex.cpp
* compressedtex.h
 Specialized loading routines for compressed textures (mostly dds).

* cubemap.cpp
* cubemap.h
 Loading of environment maps e.g. skies or for reflections.

* format.cpp
* format.h
 Small helper functions to organize which OpenGL formats to use.

* legacyslotload.cpp
 Legacy texture slot loading (sauerbraten alike).

* macros.h
* scale.h
 Small headers with some widely used macros.

* modifiers.cpp
* modifiers.h
 Texture modifiers effecting e.g. texture size, color, ... Mainly applied on load.

* savetexture.cpp
* savetexture.h
 Everything to save images of various formats.

* SDL_loading.cpp
* SDL_loading.h
 Backend: Wrapper for the SDL API calls used to load textures.

* texsettings.cpp
* texsettings.h
 Settings for texture loading and handling. Used so globals can be minimized in future.

* texture.cpp
* texture.h
  (Old) Main texture loading and providing the texture registry.

* slotset.cpp
* slotset.h
  slotsets are used to load texture-slots in chunks.
  namespace: inexor::slotset

* slot.cpp
* slot.h
  Management of texture slots (slots = textures like they are visible ingame).
