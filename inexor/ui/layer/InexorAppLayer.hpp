#pragma once
#include "include/cef_app.h"

#include "inexor/ui/context/InexorContextProvider.hpp"
#include "inexor/ui/layer/InexorLayerProvider.hpp"

namespace inexor {
namespace ui {
namespace layer {

extern SharedVar<int> showapplayer;

/**
 * The application layer of the inexor user interface.
 */
class InexorAppLayer : public inexor::ui::context::InexorContextProvider,
                       public AbstractInexorLayerProvider
{

    public:
        InexorAppLayer(std::string &name, std::string &url)
            : AbstractInexorLayerProvider(name, url),
			  _name(name),
			  _url(url) {};

        // InexorCefContextProvider
        void InitializeContext() override;
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception) override;
        std::string GetContextName() override { return _name; };

        // User interface resize handling
        void Reload();
        void Resize(int x, int y, int width, int height);
        void AutoResize(int width, int height);

        // Intercept setters for event handling
        void SetVisibility(bool _is_visible) override;
        void SetAcceptingKeyInput(bool _is_accepting_key_input) override;
        void SetAcceptingMouseInput(bool _is_accepting_mouse_input) override;

        // Event handling
        void FireUiEvent(std::string name, bool value);
        void FireUiEvent(std::string name, std::string value);

    private:
        std::string _name;
        std::string _url;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(InexorAppLayer);
};

}
}
}
