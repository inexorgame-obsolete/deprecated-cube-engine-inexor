#ifndef INEXOR_UI_INEXOR_FRAME_HEADER
#define INEXOR_UI_INEXOR_FRAME_HEADER

#include "include/cef_app.h"

#include "inexor/ui/InexorContextProvider.hpp"
#include "inexor/ui/InexorLayerProvider.hpp"

extern int uimenuvisible;
extern char* uimenustate;
extern char* uimenuparentstate;

/**
 * The main user interface of inexor.
 */
class InexorUserInterface : public InexorContextProvider,
                            public AbstractInexorLayerProvider
{

    public:
        InexorUserInterface(std::string &name, std::string &url)
            : AbstractInexorLayerProvider(name, url),
			  _name(name),
			  _url(url),
			  menu_visible(true),
			  menu_state("/menu/main"),
			  menu_parent_state("") {};

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return _name; };

        void Reload() {
            std::string url = GetUrl();
            SetUrl(url);
        };

        void Resize(int x, int y, int width, int height) {
            if (is_visible && layer.get()) {
                std::cerr << "Resize inexor user interface: (" << x << ", " << y << ", " << width << ", " << height << ")\n";
                if (layer->GetInexorRenderHandler()->SetViewRect(x, y, width, height)) {
                    layer->GetBrowser()->GetHost()->WasResized();
                }
            }
        };

        void AutoResize(int width, int height) {
            if (layer.get()) {
                if (width != layer->GetInexorRenderHandler()->GetViewWidth() || height != layer->GetInexorRenderHandler()->GetViewHeight()) {
                    Resize(0, 0, width, height);
                }
            }
        };

        /// Bind to key ESC
        void Menu() {
            if (is_visible) {
                if (menu_parent_state == "") {
                    if (!mainmenu) {
                        menu_visible = false;
            	    }
                } else {
                    this->menu_state = menu_state;
                }
            } else {
                this->menu_state = "/menu/main";
            }
        };

        bool IsMenuVisible() { return menu_visible; };
        std::string GetMenuState() { return menu_state; };
        std::string GetMenuParentState() { return menu_parent_state; };

        /// Updates the menu states
        void SetMenuStates(std::string menu_state, std::string menu_parent_state, bool menu_visible) {
            this->menu_state = menu_state;
            this->menu_parent_state = menu_parent_state;
            this->menu_visible = menu_visible;
        };

    private:
        std::string _name;
        std::string _url;

        bool menu_visible;
        std::string menu_state;
        std::string menu_parent_state;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorUserInterface);
};

#endif
