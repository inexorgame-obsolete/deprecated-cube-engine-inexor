#ifndef _CEF_SETTINGS_H
#define _CEF_SETTINGS_H
#pragma once

#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class InexorCefSettings : public CefSettings {
    public:
	    InexorCefSettings() {
	    	no_sandbox = true;
	    	ignore_certificate_errors = true;
	        multi_threaded_message_loop = false;
	        windowless_rendering_enabled = true;
	        command_line_args_disabled = true;
	        log_severity = LOGSEVERITY_INFO;
	        single_process = true;
	        char base_path[FILENAME_MAX];
	        GetCurrentDir(base_path, sizeof(base_path));
	        CefString(&resources_dir_path).FromString(std::string(base_path) + "/src/libraries/cef3/Resources");
	        CefString(&locales_dir_path).FromString(std::string(base_path) + "/src/libraries/cef3/Resources/locales");
	        CefString(&log_file).FromString(std::string(base_path) + "/inexorcef.log");
        };
};

#endif
