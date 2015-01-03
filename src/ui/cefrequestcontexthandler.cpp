#include "cefrequestcontexthandler.h"

InexorCefRequestContextHandler::InexorCefRequestContextHandler()
{
	cookieManager = CefCookieManager::CreateManager("/tmp/inexorc", false);
}

InexorCefRequestContextHandler::~InexorCefRequestContextHandler()
{
}

CefRefPtr<CefCookieManager> InexorCefRequestContextHandler::GetCookieManager()
{
	return cookieManager;
}
