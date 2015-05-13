#ifndef _CEF_DEBUG_H
#define _CEF_DEBUG_H

#include <string>

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"

void cefdebug(std::string method_name, std::string message);
void cefdebugargs(const CefV8ValueList& arguments);

extern void logoutf(const char *fmt, ...);

#endif  // _CEF_DEBUG_H
