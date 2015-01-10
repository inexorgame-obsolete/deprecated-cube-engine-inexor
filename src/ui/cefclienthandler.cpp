#include <sstream>

#include "cefclienthandler.h"

extern void logoutf(const char *fmt, ...);

InexorCefClientHandler::InexorCefClientHandler(InexorCefRenderHandler *renderHandler) : render_handler(renderHandler)
{
	browser_id = -1;
	browser_count = 0;
	is_closing = false;
	cookie_manager = CefCookieManager::CreateManager("/tmp/inexorc", false);
}

InexorCefClientHandler::~InexorCefClientHandler() { }

void InexorCefClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    if (!browser.get())   {
        // Keep a reference to the main browser.
        this->browser = browser;
        browser_id = browser->GetIdentifier();
    }
    // Keep track of how many browsers currently exist.
    browser_count++;
}

bool InexorCefClientHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed description of this
    // process.
    if (browser_id == browser->GetIdentifier()) {
        // Notify the browser that the parent window is about to close.
    	// browser->GetHost()->ParentWindowWillClose();
    	// Set a flag to indicate that the window close should be allowed.
    	is_closing = true;
    }
    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void InexorCefClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    if (browser_id == browser->GetIdentifier()) {
        // Free the browser pointer so that the browser can be destroyed.
        browser = NULL;
    }
    if (--browser_count == 0) {
        // All browser windows have closed. Quit the application message loop.
        // CefQuitMessageLoop();
        logoutf("InexorCefClientHandler::OnBeforeClose");
    }
}

void InexorCefClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD();
    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;
    logoutf("Failed to load URL %s: %s", failedUrl.c_str(), errorText.c_str());
    // Display a load error message.
    std::stringstream error_message;
    error_message << "<html><body><h2>Failed to load URL " << std::string(failedUrl)
                  << " with error " << std::string(errorText) << " (" << errorCode
                  << ").</h2></body></html>";
    frame->LoadString(error_message.str(), failedUrl);
}

bool InexorCefClientHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut) {
    CEF_REQUIRE_UI_THREAD();
    // logoutf("InexorCefClientHandler::OnPreKeyEvent: key_event.type: %d native_key_code: %d windows_key_code: %d is_system_key: %d", key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
	return false;
}

bool InexorCefClientHandler::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event) {
    CEF_REQUIRE_UI_THREAD();
    // logoutf("InexorCefClientHandler::OnKeyEvent: key_event.type: %d native_key_code: %d windows_key_code: %d is_system_key: %d", key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

void InexorCefClientHandler::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url)
{
    CEF_REQUIRE_UI_THREAD();
    logoutf("address change: %s", url.ToString().c_str());
}

void InexorCefClientHandler::OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value)
{
    CEF_REQUIRE_UI_THREAD();
    logoutf("status: %s", value.ToString().c_str());
}

bool InexorCefClientHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line)
{
    CEF_REQUIRE_UI_THREAD();
    logoutf("jsconsole [%s (%d)]: %s", source.ToString().c_str(), line, message.ToString().c_str());
	return true;
}
