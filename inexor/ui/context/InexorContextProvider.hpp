#ifndef INEXOR_UI_INEXOR_CONTEXT_PROVIDER_HEADER
#define INEXOR_UI_INEXOR_CONTEXT_PROVIDER_HEADER

#include <list>

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

#include "inexor/util/Logging.hpp"

namespace inexor {
namespace ui {
namespace context {

class InexorContextProvider : public CefV8Handler,
                              public CefV8Accessor
{
    public:
        // Initializes the context (or subcontext of a context) as a V8 object
        virtual void InitializeContext() = 0;

        // The name of the object
        virtual std::string GetContextName() = 0;

        // Returns the common context as a V8 object
        CefRefPtr<CefV8Value> GetContext();

        // Hierarchical sub contexts are automatically initialized
        void InitializeSubContexts();
        void AddSubContext(InexorContextProvider* sub_context);

    protected:
        std::list<InexorContextProvider*> sub_contexts;

        CefRefPtr<CefV8Value> context;

        // Helper Methods for reducing verbose code
        void CreateFunction(const CefString& name);
        void CreateFunction(const CefString& name, CefRefPtr<CefV8Handler> handler);
        void CreateVariable(const CefString& name, bool readonly = false);
        void CreateSubContext(CefRefPtr<InexorContextProvider> sub_context);

};

}
}
}

#endif
