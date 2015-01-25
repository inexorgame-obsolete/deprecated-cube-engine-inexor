/*
 * EntityAction.cpp
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#include "EntityFunction.h"
#include "TypeBase.h"
#include "EntityType.h"
#include "RelationshipType.h"
#include "EntityInstance.h"
#include "RelationshipInstance.h"

/*
void EntityFunction::Execute() {
    logoutf("execute, Without parameters");
};

void EntityFunction::Execute(TypeBase* type)
{
    logoutf("execute, Type: TypeBase, Type Name: %s", type->GetName().c_str());
};

void EntityFunction::Execute(EntityType* type)
{
    logoutf("execute, Type: EntityType, Type Name: %s", type->GetName().c_str());
};

void EntityFunction::Execute(RelationshipType* type)
{
    logoutf("execute, Type: RelationshipType, Type Name: %s", type->GetName().c_str());
};

void EntityFunction::Execute(EntityInstance* inst)
{
    logoutf("execute, Type: EntityInstance, Type Name: %s", inst->GetType()->GetName().c_str());
};

void EntityFunction::Execute(RelationshipInstance* inst)
{
    logoutf("execute, Type: RelationshipInstance, Type Name: %s", inst->GetType()->GetName().c_str());
};
*/

void EntityFunction::operator()()
{
    Execute();
}

void EntityFunction::operator()(TypeBase* type)
{
    Execute(type);
}

void EntityFunction::operator()(EntityType* type)
{
    Execute(type);
}

void EntityFunction::operator()(RelationshipType* type)
{
    Execute(type);
}

void EntityFunction::operator()(EntityInstance* inst)
{
    Execute(inst);
}

void EntityFunction::operator()(RelationshipInstance* inst)
{
    Execute(inst);
}

void FunctionRefPtr::operator()()
{
    get()->Execute();
}

void FunctionRefPtr::operator()(TypeBase* type)
{
    get()->Execute(type);
}

void FunctionRefPtr::operator()(EntityType* type)
{
    get()->Execute(type);
}

void FunctionRefPtr::operator()(RelationshipType* type)
{
    get()->Execute(type);
}

void FunctionRefPtr::operator()(EntityInstance* inst)
{
    get()->Execute(inst);
}

void FunctionRefPtr::operator()(RelationshipInstance* inst)
{
    get()->Execute(inst);
}
