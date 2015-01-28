/*
 * VelocityTransformation.h
 *
 *  Created on: 28.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_

#include "../../../EntitySystemBase.h"
#include "../../../domain/graph/EntityFunction.h"

class VelocityTransformation : public EntityFunction
{
    public:
        VelocityTransformation();
        virtual ~VelocityTransformation();

        void Execute(EntityInstance* particle, float time_factor);

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(VelocityTransformation);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_MODIFIER_VELOCITYTRANSFORMATION_H_ */
