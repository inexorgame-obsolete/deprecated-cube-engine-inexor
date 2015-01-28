/*
 * VectorField.h
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VECTORFIELD_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VECTORFIELD_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"

class VectorField : public EntityFunction
{
    public:
        VectorField(std::string expression);
        virtual ~VectorField();

        void Execute(EntityInstance* modifier, EntityInstance* particle, float time_factor);

    private:
        mu::Parser parser;
        int args;
        std::string expression;
        mu::value_type ix;
        mu::value_type iy;
        mu::value_type iz;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(VectorField);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VECTORFIELD_H_ */
