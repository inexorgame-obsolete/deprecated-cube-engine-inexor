#ifndef _CEF_EVENT_MANAGER_H
#define _CEF_EVENT_MANAGER_H

#include "cefevent.h"

class InexorCefEventManager : public InexorCefContextProvider
{

    public:
        InexorCefEventManager() {};

        InexorCefEvent* GetEvent(const CefString& name);
        void SubscribeEvent(const CefString& name, InexorCefCallback *callback);

        void FireEventWithContext(const CefString& name, const InexorCefValueList& arguments);
        void FireEvent(const CefString& name, const CefV8ValueList& arguments);

        // InexorCefContextProvider
        void InitializeContext();
        bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval, CefString& exception);
        bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception);
        std::string GetContextName() { return "event"; };

    private:
        std::list<InexorCefEvent*> events;

        IMPLEMENT_REFCOUNTING(InexorCefEventManager);

};

#endif  // _CEF_EVENT_H
