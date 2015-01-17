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
      uuid(0)
{
}

TypeBase::~TypeBase()
{
}

