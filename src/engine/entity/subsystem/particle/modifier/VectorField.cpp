/*
 * VectorField.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "VectorField.h"

namespace inexor {
namespace entity {
namespace particle {

VectorField::VectorField(std::string expression)
    : EntityFunction("vector_field"), args(3), expression(expression)
{
    // TODO: check this -> use mu::value_type as EntityAttribute
    parser.DefineVar("x", &ix);
    parser.DefineVar("y", &iy);
    parser.DefineVar("z", &iz);
    // TODO: check this -> add modfier position variables: mx, my, mz
	parser.SetExpr(expression);
}

VectorField::~VectorField()
{
}

void VectorField::Before(TimeStep time_step, EntityInstance* modifier)
{
    parser.SetExpr(modifier->GetType()->GetAttribute("expression")->GetString());
    // TODO: check for existence: x, y and z
    // TODO: check for existence: expression
}

void VectorField::After(TimeStep time_step, EntityInstance* inst)
{

}

// Without modifier, expression was set on function creation!
void VectorField::Execute(TimeStep time_step, EntityInstance* particle)
{
    // TODO: check this -> use mu::value_type as EntityAttribute
	ix = (*particle)[POS]->vec3Val.x;
	iy = (*particle)[POS]->vec3Val.y;
	iz = (*particle)[POS]->vec3Val.z;
	try {
		mu::value_type *v = parser.Eval(args);
		(*particle)[VELOCITY]->vec3Val.add(vec(v[0] * time_step.time_factor, v[1] * time_step.time_factor, v[2] * time_step.time_factor));
	} catch (mu::Parser::exception_type &e) {
		logoutf("Error parsing vector field expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
	}
}

/**
 * The base position is the modifiers position.
 */
void VectorField::Execute(TimeStep time_step, EntityInstance* modifier, EntityInstance* particle)
{
    // TODO: check this -> use mu::value_type as EntityAttribute
	ix = (*particle)["x"]->doubleVal - (*modifier)["x"]->doubleVal;
	iy = (*particle)["y"]->doubleVal - (*modifier)["y"]->doubleVal;
	iz = (*particle)["z"]->doubleVal - (*modifier)["z"]->doubleVal;
    // TODO: check this -> add modifier position variables: mx, my, mz
	try {
		// parser.SetExpr(modifier->GetType()->GetAttribute("expression")->GetString());
		mu::value_type *v = parser.Eval(args);
        (*particle)["vx"]->doubleVal = (*particle)["vx"] + v[0] * time_step.time_factor;
        (*particle)["vy"]->doubleVal = (*particle)["vy"] + v[1] * time_step.time_factor;
        (*particle)["vz"]->doubleVal = (*particle)["vz"] + v[2] * time_step.time_factor;
	} catch (mu::Parser::exception_type &e) {
		logoutf("Error parsing vector field expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
	}
}

}
}
}
