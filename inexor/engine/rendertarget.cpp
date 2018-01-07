#include "inexor/engine/rendertarget.hpp"

void rendertarget::cleanup(bool fullclean)
{
    if(renderfb) { glDeleteFramebuffers_(1, &renderfb); renderfb = 0; }
    if(renderdb) { glDeleteRenderbuffers_(1, &renderdb); renderdb = 0; }
    if(rendertex) { glDeleteTextures(1, &rendertex); rendertex = 0; }
    texw = texh = 0;
    cleanupblur();

    if(fullclean) colorfmt = depthfmt = GL_FALSE;
}
