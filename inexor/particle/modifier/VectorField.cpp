/*
 * VectorField.cpp
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#include "VectorField.hpp"

namespace inexor {
namespace entity {
namespace particle {

    VectorField::VectorField(std::string expression)
        : EntityFunction(MODIFIER_VECTOR_FIELD_FUNCTION), args(3), expression(expression)
    {
        parser.DefineVar("x", &ix);
        parser.DefineVar("y", &iy);
        parser.DefineVar("z", &iz);
        // TODO: check this -> add modfier position variables: mx, my, mz
	    parser.SetExpr(expression);
    }

    VectorField::~VectorField()
    {
    }

    void VectorField::SetExpression(std::string expression)
    {
        if (this->expression != expression)
        {
            this->expression = expression;
            parser.SetExpr(expression);
        }
    }

    void VectorField::Before(TimeStep time_step, std::shared_ptr<EntityInstance> modifier)
    {
        // TODO: check performance
        SetExpression(modifier->GetType()[EXPRESSION]->stringVal);
        // TODO: check for existence: x, y and z
        // TODO: check for existence: expression
    }

    /**
     * The base position is the modifiers position.
     */
    AttributeRefPtr VectorField::Execute(TimeStep time_step, std::shared_ptr<EntityInstance> modifier, std::shared_ptr<EntityInstance> particle)
    {
        // TODO: check this -> add modifier position variables: mx, my, mz
        ix = (*particle)[POS]->vec3Val.x - (*modifier)[POS]->vec3Val.x;
        iy = (*particle)[POS]->vec3Val.y - (*modifier)[POS]->vec3Val.y;
        iz = (*particle)[POS]->vec3Val.z - (*modifier)[POS]->vec3Val.z;
        try {
            mu::value_type *v = parser.Eval(args);
            vec vel(v[0] * time_step.time_factor, v[1] * time_step.time_factor, v[2] * time_step.time_factor);
            (*particle)[VELOCITY]->vec3Val.add(vel);
        } catch (mu::Parser::exception_type &e) {
            spdlog::get("global")->debug() << "Error parsing vector field expression " << e.GetExpr().c_str() << ": " << e.GetMsg().c_str();
            return false;
        }
        return true;
    }

    void VectorField::After(TimeStep time_step, std::shared_ptr<EntityInstance> modifier)
    {
    }

}
}
}
