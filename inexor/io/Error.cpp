#include <stdlib.h>                      // for exit, EXIT_FAILURE
#include <memory>                        // for __shared_ptr

#include "inexor/io/Error.hpp"
#include "inexor/io/Logging.hpp"         // for Log, Logger, log_manager

/// Fatal crash: log/display crash message and clean up SDL.
void fatal(const char *s, ...)
{
    cleanup_application();
    static int errors = 0;
    errors++;
    if(errors <= 2) // print up to one extra recursive error
    {
        defvformatstring(msg,s,s);
        Log.std->critical(msg);

#ifdef WIN32
        if(errors <= 1) MessageBox(NULL, msg, "Inexor fatal error", MB_OK|MB_SYSTEMMODAL);
#endif
    }
    exit(EXIT_FAILURE);
}

/// Fatal crash: log/display crash message and clean up SDL.
void fatal(std::vector<std::string> &output)
{
    cleanup_application();
    std::string completeoutput;
    for(const std::string &message : output) {
        Log.std->critical(message);
        completeoutput += message;
    }
#ifdef WIN32
    MessageBox(NULL, completeoutput.c_str(), "Inexor fatal error", MB_OK | MB_SYSTEMMODAL);
#endif
    exit(EXIT_FAILURE);
}
