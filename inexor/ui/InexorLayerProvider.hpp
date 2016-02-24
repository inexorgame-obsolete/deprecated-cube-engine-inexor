#ifndef INEXOR_UI_INEXOR_LAYER_PROVIDER_HEADER
#define INEXOR_UI_INEXOR_LAYER_PROVIDER_HEADER

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include "inexor/ui/InexorLayer.hpp"

class InexorLayerProvider
{

    public:
        InexorLayerProvider() {};
        virtual ~InexorLayerProvider() {};

        void SetLayer(CefRefPtr<InexorLayer> layer) { this->layer = layer; }
        virtual std::string GetContextName() = 0;
        virtual std::string GetUrl() = 0;
        virtual bool GetVisibility() = 0;
        virtual bool GetAcceptingInput() = 0;
        virtual bool GetFocus() = 0;

    protected:
        CefRefPtr<InexorLayer> layer;

        std::string GetLocalUrl(std::string relpath) {
            char base_path[FILENAME_MAX];
            GetCurrentDir(base_path, sizeof(base_path));
            return "file://" + std::string(base_path) + relpath;
        };

        IMPLEMENT_REFCOUNTING(InexorLayerProvider);
};

class AbstractInexorLayerProvider : public InexorLayerProvider
{
    public:
        AbstractInexorLayerProvider() : is_visible(false) {};
        virtual ~AbstractInexorLayerProvider() {};

        void Show() { SetVisibility(true); };
        void Hide() { SetVisibility(false); };
        void Toggle() { SetVisibility(!is_visible); };

        bool GetVisibility() { return is_visible; };
        bool GetAcceptingInput() { return is_visible; };
        bool GetFocus() { return is_visible; };

        void SetVisibility(bool visible) {
            this->is_visible = visible;
            layer->SetVisibility(visible);
            layer->SetIsAcceptingInput(visible);
            layer->SetFocus(visible);
        };

    protected:
        bool is_visible;

};

#endif
