/*
 * TimeStep.hpp
 *
 *  Created on: 30.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_DOMAIN_TIMESTEP_H_
#define SRC_ENGINE_ENTITY_DOMAIN_TIMESTEP_H_

namespace inexor {
namespace entity {

    /**
     *
     */
    class TimeStep
    {
        public:

            /**
            *
            */
            TimeStep(int elapsed_millis, double time_factor, double time_unit);

            /**
             *
             */
            TimeStep(int elapsed_millis, double time_unit);

            virtual ~TimeStep();

            int elapsed_millis;
            double time_factor;
            double time_unit;
    };

}
}

#endif /* SRC_ENGINE_ENTITY_DOMAIN_TIMESTEP_H_ */
