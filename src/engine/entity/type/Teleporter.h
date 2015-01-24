/*
 * Teleporter.h
 *
 *  Created on: 18.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_TYPE_TELEPORTER_H_
#define SRC_ENGINE_ENTITY_TYPE_TELEPORTER_H_

#include "../EntityType.h"

#define ENTTYPE_TELEPORT "teleport"
#define ENTTYPE_TELEDEST "teledest"
#define RELTYPE_TELEPORTS_TO "teleports_to"

class TeleporterType : public EntityType
{
    public:
        TeleporterType();
        virtual ~TeleporterType();
};

#endif /* SRC_ENGINE_ENTITY_TYPE_TELEPORTER_H_ */
