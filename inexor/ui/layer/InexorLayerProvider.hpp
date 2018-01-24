#pragma once

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

#include "inexor/ui/layer/InexorLayer.hpp"

namespace inexor {
namespace ui {
namespace layer {

class InexorLayerProvider : public CefBaseRefCounted
{

    public:
        InexorLayerProvider() {};
        ~InexorLayerProvider() override {};

        void SetLayer(CefRefPtr<InexorLayer> layer) { this->layer = layer; }

        virtual std::string GetLayerName() = 0;
        virtual void SetLayerName(std::string &_name) = 0;

        virtual std::string GetUrl() = 0;
        virtual void SetUrl(std::string &_url) = 0;

        virtual bool GetVisibility() = 0;
        virtual void SetVisibility(bool _is_visible) = 0;

        virtual bool GetAcceptingKeyInput() = 0;
        virtual void SetAcceptingKeyInput(bool _is_accepting_key_input) = 0;

        virtual bool GetAcceptingMouseInput() = 0;
        virtual void SetAcceptingMouseInput(bool _is_accepting_mouse_input) = 0;

    protected:
        CefRefPtr<InexorLayer> layer;

        std::string GetLocalUrl(std::string relpath) {
            char base_path[FILENAME_MAX];
            GetCurrentDir(base_path, sizeof(base_path));
            return "file://" + std::string(base_path) + relpath;
        };

    private:
        IMPLEMENT_REFCOUNTING(InexorLayerProvider);
};

class AbstractInexorLayerProvider : public InexorLayerProvider
{
    public:
        AbstractInexorLayerProvider() : is_visible(false) {};
        AbstractInexorLayerProvider(std::string &name) : is_visible(false), name(name) {}
        AbstractInexorLayerProvider(std::string &name, std::string &url) : is_visible(false), name(name), url(url) {};
        ~AbstractInexorLayerProvider() override {};

        std::string GetLayerName() override { return name; };
        void SetLayerName(std::string &_name) override {
            name = _name;
        };

        std::string GetUrl() override { return url; };
        void SetUrl(std::string &_url) override {
            url = _url;
        };

        bool GetVisibility() override { return is_visible; };
        void SetVisibility(bool _is_visible) override {
            this->is_visible = _is_visible;
            if (layer.get()) layer->SetVisibility(_is_visible);
        };

        bool GetAcceptingKeyInput() override { return is_accepting_key_input; };
        void SetAcceptingKeyInput(bool _is_accepting_key_input) override {
            this->is_accepting_key_input = _is_accepting_key_input;
            if (layer.get()) layer->SetIsAcceptingKeyInput(_is_accepting_key_input);
        };

        bool GetAcceptingMouseInput() override { return is_accepting_mouse_input; };
        void SetAcceptingMouseInput(bool _is_accepting_mouse_input) override {
            this->is_accepting_mouse_input = _is_accepting_mouse_input;
            if (layer.get()) layer->SetIsAcceptingMouseInput(_is_accepting_mouse_input);
        };

        void Show() {
            SetVisibility(true);
            SetAcceptingKeyInput(true);
            SetAcceptingMouseInput(true);
        };
        void Hide() {
            SetVisibility(false);
            SetAcceptingKeyInput(false);
            SetAcceptingMouseInput(false);
        };
        void ToggleVisibility() {
            SetVisibility(!is_visible);
        };

    protected:
        bool is_visible;
        bool is_accepting_key_input;
        bool is_accepting_mouse_input;
        std::string name;
        std::string url;

};

}
}
}
