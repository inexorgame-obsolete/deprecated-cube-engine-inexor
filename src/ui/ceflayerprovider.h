#ifndef _CEF_LAYER_PROVIDER_H
#define _CEF_LAYER_PROVIDER_H

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

#include "ceflayer.h"

class InexorCefLayerProvider
{

    public:
        void SetLayer(CefRefPtr<InexorCefLayer> layer) { this->layer = layer; }
        virtual std::string GetContextName() = 0;
        virtual std::string GetUrl() = 0;
        virtual bool GetVisibility() = 0;
        virtual bool GetAcceptingInput() = 0;
        virtual bool GetFocus() = 0;

    protected:
        CefRefPtr<InexorCefLayer> layer;

};

#endif  // _CEF_LAYER_PROVIDER_H
