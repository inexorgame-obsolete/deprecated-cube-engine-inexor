#ifndef _CEF_SETTINGS_H
#define _CEF_SETTINGS_H
#pragma once

class InexorCefSettings : public CefSettings {
    public:
	    InexorCefSettings() {
	    	no_sandbox = false;
	    	ignore_certificate_errors = true;
	        multi_threaded_message_loop = false;
	        windowless_rendering_enabled = true;
	        log_severity = LOGSEVERITY_VERBOSE;
	        // log_file = "inexorcef.log";
	        // resources_dir_path = "src/libraries/cef3/Resources";
	        // locales_dir_path = "src/libraries/cef3/Resources/locales";
	        CefString(&log_file).FromASCII("inexorcef.log");
	        CefString(&resources_dir_path).FromASCII("src/libraries/cef3/Resources");
	        CefString(&locales_dir_path).FromASCII("src/libraries/cef3/Resources/locales");
        };
};

#endif
