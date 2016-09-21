#ifndef INEXOR_VSCRIPT_FACTORY_BOOLMEMORYTYPEFACTORY_HEADER
#define INEXOR_VSCRIPT_FACTORY_BOOLMEMORYTYPEFACTORY_HEADER

#include "inexor/entity/factory/EntityTypeFactory.hpp"
#include "inexor/entity/domain/TypeRefPtr.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityType.hpp"
#include "inexor/entity/domain/graph/RelationshipType.hpp"
#include "inexor/entity/manager/EntityTypeManager.hpp"
#include "inexor/entity/manager/RelationshipTypeManager.hpp"
#include "inexor/vscript/model/VScriptModel.hpp"

using namespace inexor::entity;

namespace inexor {
namespace vscript {

    /**
     *
     */
    class BoolMemoryTypeFactory : public EntityTypeFactory
    {
        public:

            /**
             *
             */
            BoolMemoryTypeFactory(std::shared_ptr<EntityTypeManager> entity_type_manager);
            virtual ~BoolMemoryTypeFactory();

            /**
             *
             */
            TypeRefPtr<EntityType> Create(std::string name_suffix);

            /**
             *
             */
            TypeRefPtr<EntityType> Create(std::string name_suffix, bool value);

        private:

            // Include the default reference counting implementation.
            IMPLEMENT_REFCOUNTING(BoolMemoryTypeFactory);
    };

}
}

#endif /* INEXOR_VSCRIPT_FACTORY_BOOLMEMORYTYPEFACTORY_HEADER */
