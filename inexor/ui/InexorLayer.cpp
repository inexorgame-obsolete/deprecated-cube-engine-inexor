#include <iostream>

#include "inexor/util/Logging.hpp"
#include "inexor/ui/InexorLayer.hpp"

using namespace inexor::util;

InexorLayer::InexorLayer(std::string name, int x, int y, int width, int height, std::string url)
    : name(name),
      url(url),
      is_visible(false),
      is_accepting_key_input(false),
      is_accepting_mouse_input(false),
      browser_id(-1),
      browser_count(0),
      is_closing(false)
{
    std::cerr << "init: cef: creating layer\n  name: " << name << "\n  url: " << url << "\n  x: " << x << "\n  y: " << y << "\n  width: " << width << "\n  height " << height << ")\n";
    window_info.x = x;
    window_info.y = y;
    window_info.width = width;
    window_info.height = height;
    cookie_manager = CefCookieManager::CreateManager("/tmp/inexorc", false, NULL);
    render_handler = new InexorRenderHandler(true, x, y, width, height);
    browser = CefBrowserHost::CreateBrowserSync(window_info, this, url, browser_settings, NULL);
    if (browser.get()) {
        spdlog::get("global")->debug() << "init: cef: created layer " << quoted(name.c_str());
        UpdateFocus();
    }
}

InexorLayer::~InexorLayer() { }

void InexorLayer::SetVisibility(bool is_visible)
{
    std::cerr << "InexorLayer::SetVisibility()\n";
	this->is_visible = is_visible;
	browser->GetHost()->SetWindowVisibility(is_visible);
	browser->GetHost()->WasHidden(!is_visible);
}

void InexorLayer::UpdateFocus()
{
    browser->GetHost()->SendFocusEvent(is_accepting_key_input || is_accepting_mouse_input);
}

void InexorLayer::SetIsAcceptingKeyInput(bool is_accepting_key_input)
{
    std::cerr << "InexorLayer::SetIsAcceptingKeyInput()\n";
	this->is_accepting_key_input = is_accepting_key_input;
	UpdateFocus();
}

void InexorLayer::SetIsAcceptingMouseInput(bool is_accepting_mouse_input)
{
    std::cerr << "InexorLayer::SetIsAcceptingMouseInput()\n";
    this->is_accepting_mouse_input = is_accepting_mouse_input;
    UpdateFocus();
}

void InexorLayer::Destroy()
{
    if(browser.get())
        browser->GetHost()->CloseBrowser(true);
}

void InexorLayer::Copy()
{
    if (browser.get()) {
        browser->GetFocusedFrame()->Copy();
    }
}

void InexorLayer::Paste()
{
    if (browser.get()) {
        browser->GetFocusedFrame()->Paste();
    }
}

void InexorLayer::Cut()
{
    if (browser.get()) {
        browser->GetFocusedFrame()->Cut();
    }
}

void InexorLayer::ShowDevTools()
{
    if (browser.get()) {
        browser->GetHost()->ShowDevTools(window_info, this, browser_settings, CefPoint());
    }
}

void InexorLayer::OnAfterCreated(CefRefPtr<CefBrowser> browser)
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

bool InexorLayer::DoClose(CefRefPtr<CefBrowser> browser)
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

void InexorLayer::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    if (browser_id == browser->GetIdentifier()) {
        // Free the browser pointer so that the browser can be destroyed.
        browser = NULL;
    }
    if (--browser_count == 0) {
        // All browser windows have closed. Quit the application message loop.
        //CefQuitMessageLoop();
        //spdlog::get("global")->debug() << "InexorCefLayer::OnBeforeClose()";
    }
}

void InexorLayer::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD();
    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;
    spdlog::get("global")->error() << "Failed to load URL " << failedUrl.ToString() << ": " << errorText.ToString();
    // Display a load error message.
    std::stringstream error_message;
    error_message << "<html><body><h2>Failed to load URL " << std::string(failedUrl)
                  << " with error " << std::string(errorText) << " (" << errorCode
                  << ").</h2></body></html>";
    frame->LoadString(error_message.str(), failedUrl);
}

bool InexorLayer::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event, bool* is_keyboard_shortcut) {
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug("InexorCefLayer::OnPreKeyEvent: key_event.type: {0} native_key_code: {1} windows_key_code: {2} is_system_key: {3}",
                                 key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

bool InexorLayer::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& key_event, CefEventHandle os_event) {
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug("InexorCefLayer::OnKeyEvent: key_event.type: {0} native_key_code: {1} windows_key_code: {2} is_system_key: {3}",
                                     key_event.type, key_event.native_key_code, key_event.windows_key_code, key_event.is_system_key);
    return false;
}

void InexorLayer::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url)
{
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug() << "address change: " << url.ToString();
}

void InexorLayer::OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value)
{
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug() << "status: " << value.ToString();
}

bool InexorLayer::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line)
{
    CEF_REQUIRE_UI_THREAD();
    spdlog::get("global")->debug("status: {0} ({1}): {2}", source.ToString(), line, message.ToString());
    return true;
}
