#ifndef INEXOR_VSCRIPT_PROVIDER_BOOLMEMORY_HEADER
#define INEXOR_VSCRIPT_PROVIDER_BOOLMEMORY_HEADER

#include "inexor/entity/provider/EntityTypeProvider.hpp"
#include "inexor/entity/provider/RelationshipTypeProvider.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityType.hpp"
#include "inexor/entity/domain/graph/RelationshipType.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    class EntityTypeManager;

    /**
     * Defines the bool memory entity type.
     */
    class BoolMemoryEntityTypeProvider : public EntityTypeProvider
    {
        public:

            BoolMemoryEntityTypeProvider();
            virtual ~BoolMemoryEntityTypeProvider();

        private:
            
            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(BoolMemoryEntityTypeProvider);

    };

}
}

#endif /* INEXOR_VSCRIPT_PROVIDER_BOOLMEMORY_HEADER */
