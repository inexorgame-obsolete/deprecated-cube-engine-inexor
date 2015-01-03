#include <sstream>

#include "cefclienthandler.h"

extern void logoutf(const char *fmt, ...);

InexorCefClientHandler::InexorCefClientHandler(InexorCefRenderHandler *renderHandler) : m_renderHandler(renderHandler)
{
	m_BrowserId = -1;
	m_BrowserCount = 0;
	m_bIsClosing = false;
}

InexorCefClientHandler::~InexorCefClientHandler() { }

CefRefPtr<CefRenderHandler> InexorCefClientHandler::GetRenderHandler()
{
    return m_renderHandler;
};

void InexorCefClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    if (!m_Browser.get())   {
        // Keep a reference to the main browser.
        m_Browser = browser;
        m_BrowserId = browser->GetIdentifier();
    }
    // Keep track of how many browsers currently exist.
    m_BrowserCount++;
}

bool InexorCefClientHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed description of this
    // process.
    if (m_BrowserId == browser->GetIdentifier()) {
        // Notify the browser that the parent window is about to close.
    	// browser->GetHost()->ParentWindowWillClose();
    	// Set a flag to indicate that the window close should be allowed.
    	m_bIsClosing = true;
    }
    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void InexorCefClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    if (m_BrowserId == browser->GetIdentifier()) {
        // Free the browser pointer so that the browser can be destroyed.
        m_Browser = NULL;
    }
    if (--m_BrowserCount == 0) {
        // All browser windows have closed. Quit the application message loop.
        // CefQuitMessageLoop();
    }
}

void InexorCefClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) {
	CEF_REQUIRE_UI_THREAD();
    // Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
	    return;
    logoutf("Failed to load URL %s: %s", failedUrl.c_str(), errorText.c_str());
    // Display a load error message.
    std::stringstream ss;
    ss << "<html><body>"
        "<h2>Failed to load URL " << std::string(failedUrl) <<
	    " with error " << std::string(errorText) << " (" << errorCode <<
	    ").</h2></body></html>";
    frame->LoadString(ss.str(), failedUrl);
}
