/*
 * VectorField.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "VectorField.h"

VectorField::VectorField(std::string expression) : expression(expression), args(3), EntityFunction("vector_field")
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

// Without modifier, expression was set on function creation!
void VectorField::Execute(EntityInstance* particle, float time_factor)
{
    // TODO: check this -> use mu::value_type as EntityAttribute
	mu::value_type ix = particle["x"];
	mu::value_type iy = particle["y"];
	mu::value_type iz = particle["z"];
	try {
		mu::value_type *v = parser.Eval(args);
		particle["vx"] += v[0] * time_factor;
		particle["vy"] += v[1] * time_factor;
		particle["vz"] += v[2] * time_factor;
	} catch (mu::Parser::exception_type &e) {
		logoutf("Error parsing vector field expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
	}
}

// The expression is taken from the modifier
void VectorField::Execute(EntityInstance* modifier, EntityInstance* particle, float time_factor)
{
    // TODO: check this -> use mu::value_type as EntityAttribute
	mu::value_type ix = particle["x"] - modifier["x"];
	mu::value_type iy = particle["y"] - modifier["y"];
	mu::value_type iz = particle["z"] - modifier["z"];
    // TODO: check this -> add modfier position variables: mx, my, mz
	try {
		parser.SetExpr(modifier["expression"]);
		mu::value_type *v = parser.Eval(args);
		particle["vx"] += v[0] * time_factor;
		particle["vy"] += v[1] * time_factor;
		particle["vz"] += v[2] * time_factor;
	} catch (mu::Parser::exception_type &e) {
		logoutf("Error parsing vector field expression %s: %s", e.GetExpr().c_str(), e.GetMsg().c_str());
	}
}
