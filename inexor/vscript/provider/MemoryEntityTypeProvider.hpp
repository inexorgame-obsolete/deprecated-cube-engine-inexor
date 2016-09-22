#ifndef INEXOR_VSCRIPT_PROVIDER_MEMORY_HEADER
#define INEXOR_VSCRIPT_PROVIDER_MEMORY_HEADER

#include "inexor/entity/provider/EntityTypeProvider.hpp"
#include "inexor/entity/provider/RelationshipTypeProvider.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityType.hpp"
#include "inexor/entity/domain/graph/RelationshipType.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    /**
     * Defines the memory entity type.
     */
    class MemoryEntityTypeProvider : public EntityTypeProvider
    {
        public:

            MemoryEntityTypeProvider();
            virtual ~MemoryEntityTypeProvider();

    };

}
}

#endif /* INEXOR_VSCRIPT_PROVIDER_MEMORY_HEADER */
