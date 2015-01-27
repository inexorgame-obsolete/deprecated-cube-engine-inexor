/*
 * TypeBase.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "TypeBase.h"

TypeBase::TypeBase(std::string name, bool persist, bool synchronize)
    : name(name),
      persist(persist),
      synchronize(synchronize),
      uuid("")
{
}

TypeBase::TypeBase(std::string name, bool persist, bool synchronize, std::string uuid)
    : name(name),
      persist(persist),
      synchronize(synchronize),
      uuid(uuid)
{
}

TypeBase::~TypeBase()
{
}

/*
 * type["var"] = a;
 * value = type["var"];
 * type->Method(val1, val2);
 *
CefRefPtr<EntityAttribute>& TypeBase::operator[](std::string key)
{
    logoutf("get attribute: %s", key.c_str());
    return attributes[key];
}
 */

/*
CefRefPtr<EntityAction>& TypeBase::operator ->*(std::string name) {
    return actions[name];
}
*/

/*
CefRefPtr<EntityAction>& TypeBase::operator ->*(S b)
{
    return (operator*()).*memptr;
}
*/

/*
std::map<std::string, CefRefPtr<EntityAction> >& TypeBase::operator->*(std::map<std::string, CefRefPtr<EntityAction> > CefRefPtr<EntityAction>::*)
{
    return memptr[];
}
*/
