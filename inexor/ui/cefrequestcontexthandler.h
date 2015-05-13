#ifndef _CEF_REQUEST_CONTEXT_HANDLER_H
#define _CEF_REQUEST_CONTEXT_HANDLER_H
#pragma once

#include "include/cef_request_context_handler.h"
#include "include/cef_cookie.h"
#include "include/wrapper/cef_helpers.h"

class InexorCefRequestContextHandler : public CefRequestContextHandler {

    public:
        InexorCefRequestContextHandler();
        virtual ~InexorCefRequestContextHandler();

        // CefRequestContextHandler
        CefRefPtr<CefCookieManager> GetCookieManager();

    private:
        CefRefPtr<CefCookieManager> cookieManager;
        IMPLEMENT_REFCOUNTING(InexorCefRequestContextHandler);

};

#endif
