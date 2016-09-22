#include "VScriptSubsystem.hpp"

namespace inexor {
namespace vscript {

    VScriptSubsystem::VScriptSubsystem()
        : SubsystemBase(VSCRIPT_SUBSYSTEM)
    {
    }

    VScriptSubsystem::VScriptSubsystem(std::shared_ptr<EntityTypeManager> entity_type_manager,
                                       std::shared_ptr<EntityInstanceManager> entity_instance_manager,
                                       std::shared_ptr<RelationshipTypeManager> relationship_type_manager,
                                       std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager)
        : SubsystemBase(VSCRIPT_SUBSYSTEM,
                        entity_type_manager,
                        entity_instance_manager,
                        relationship_type_manager,
                        relationship_instance_manager)
    {
        // Create entity type providers
        std::shared_ptr<EntityTypeProvider> memory_provider = std::make_shared<MemoryEntityTypeProvider>();
        entity_type_manager->RegisterProvider(memory_provider);

        // Create relationship type providers
        // std::shared_ptr<RelationshipTypeProvider> teleporting_provider = new TeleportingRelationshipTypeProvider(entity_type_manager);
        // relationship_type_manager->RegisterProvider(teleporting_provider);

        InitializeModel();
    }

    VScriptSubsystem::~VScriptSubsystem()
    {
    }

    void VScriptSubsystem::Update(TimeStep time_step)
    {
        // Iterates over all events
        std::vector<InstanceRefPtr<EntityInstance> >::iterator it = event_instances.begin();
        while (it != event_instances.end())
        {
        	Activate(time_step, (*it));
            ++it;
        }
    }

    void VScriptSubsystem::Activate(TimeStep time_step, InstanceRefPtr<EntityInstance> source)
    {
    	// Iterates over all outgoing "activates" relationships for each event
    	std::list<InstanceRefPtr<RelationshipInstance> >::iterator it2 = source->outgoing[activates->uuid].begin();
        while (it2 != source->outgoing[activates->uuid].end())
        {
        	Activate(time_step, source, (*it2)->endNode, (*it2));
        	// Continue with the next outgoing relationship
            ++it2;
        }
    }

    void VScriptSubsystem::Activate(TimeStep time_step, InstanceRefPtr<EntityInstance> source, InstanceRefPtr<EntityInstance> target, InstanceRefPtr<RelationshipInstance> activates)
    {
    	// First: the relationship provides the name of the function to be called on the target node's type
        std::string activation_function_name = activates[ENT_ATTR_ACTIVATION_FUNCTION]->stringVal;

        // Second: resolve the target node's type
        FunctionRefPtr activation_function = target->GetType()[ENT_ATTR_ACTIVATION_FUNCTION]->functionVal;

        // Third: call the activation function and provide the source, the target and the relationship
        // TODO: we need a boolean result
    	activation_function->Execute(time_step, source, target, activates);
    }

    void VScriptSubsystem::Cleanup()
    {
    }

    void VScriptSubsystem::Reset()
    {
    }

    void VScriptSubsystem::InitializeModel()
    {
        // Create graph model: Node types
        parent_event_type = entity_type_manager->Create(ENT_EVENT, true, true);
        parent_memory_type = entity_type_manager->Create(ENT_MEMORY, true, true);

        FunctionRefPtr timer_event_function = std::make_shared<TimerEvent>();
        CreateEventType(ENT_TIMER_EVENT, timer_event_function);

        CreateMemoryType(ENT_BOOL_MEMORY);

        TypeRefPtr<EntityType> integer_memory_type = CreateMemoryType(ENT_INTEGER_MEMORY);
        FunctionRefPtr increase_integer_function = std::make_shared<IncreaseInteger>();
        integer_memory_type[ENT_FUNC_INCREASE_INTEGER] = increase_integer_function;
        FunctionRefPtr decrease_integer_function = std::make_shared<DecreaseInteger>();
        integer_memory_type[ENT_FUNC_DECREASE_INTEGER] = decrease_integer_function;

        // Create graph model: Relationship types
        activates = relationship_type_manager->Create(REL_ACTIVATES, false, false, ENT_ANY, ENT_ANY);

        spdlog::get("global")->debug() << "VScript subsystem graph model initialized";
    }

    TypeRefPtr<EntityType> VScriptSubsystem::CreateEventType(std::string name, InstanceRefPtr<EntityFunction> function)
    {
        TypeRefPtr<EntityType> event_type = entity_type_manager->Create(name, true, true, parent_event_type);
        event_type[ENT_ATTR_ACTIVATION_FUNCTION]->functionVal = function;
        event_types[name] = event_type;
        return event_type;
    }

    TypeRefPtr<EntityType> VScriptSubsystem::CreateMemoryType(std::string name)
    {
        TypeRefPtr<EntityType> memory_type = entity_type_manager->Create(name, true, true, parent_memory_type);
        memory_types[name] = memory_type;
        return memory_type;
    }

    InstanceRefPtr<EntityInstance> VScriptSubsystem::CreateEvent(TypeRefPtr<EntityType> event_entity_type, double x, double y, double z)
    {
        InstanceRefPtr<EntityInstance> event_entity_instance = entity_instance_manager->Create(event_entity_type);
        event_entity_instance["x"] = x;
        event_entity_instance["y"] = y;
        event_entity_instance["z"] = z;
        event_instances.push_back(event_entity_instance);
        return event_entity_instance;
    }

    InstanceRefPtr<EntityInstance> VScriptSubsystem::CreateMemory(TypeRefPtr<EntityType> memory_entity_type, double x, double y, double z, bool isConstant)
    {
        InstanceRefPtr<EntityInstance> memory_entity_instance = entity_instance_manager->Create(memory_entity_type);
        memory_entity_instance["x"] = x;
        memory_entity_instance["y"] = y;
        memory_entity_instance["z"] = z;
        memory_entity_instance["constant"] = isConstant;
        event_instances.push_back(memory_entity_instance);
        return memory_entity_instance;
    }

    InstanceRefPtr<RelationshipInstance> VScriptSubsystem::ConnectActivation(InstanceRefPtr<EntityInstance> source, InstanceRefPtr<EntityInstance> target, std::string activation_function_name)
    {
    	// Construct a new relationship instance from source to target of type "activates"
        InstanceRefPtr<RelationshipInstance> relationship_instance = relationship_instance_manager->CreateInstance(activates, source, target);
        // Set the activation function which should be called on the target.
        relationship_instance[ENT_ATTR_ACTIVATION_FUNCTION] = activation_function_name;
        return relationship_instance;
    }

    /**
     * Removes the given activation relationship.
     */
    void VScriptSubsystem::DisconnectActivation(InstanceRefPtr<RelationshipInstance> activation)
    {
    	// TODO: implement
    	spdlog::get("global")->error() << "VScriptSubsystem::DisconnectActivation() not implemented";
    }

    /**
     * Removes all existing activations between the two given entities.
     */
    void VScriptSubsystem::DisconnectAllActivations(InstanceRefPtr<EntityInstance> source, InstanceRefPtr<EntityInstance> target)
    {
    	// TODO: implement
    	spdlog::get("global")->error() << "VScriptSubsystem::DisconnectAllActivations() not implemented";
    }

    /**
     * Removes all outgoing activations of the given entity.
     */
    void VScriptSubsystem::DisconnectAllOutgoingActivations(InstanceRefPtr<EntityInstance> source)
    {
    	// TODO: implement
    	spdlog::get("global")->error() << "VScriptSubsystem::DisconnectAllOutgoingActivations() not implemented";
    }

    /**
     * Removes all incoming activations of the given entity.
     */
    void VScriptSubsystem::DisconnectAllIncomingActivations(InstanceRefPtr<EntityInstance> target)
    {
    	// TODO: implement
    	spdlog::get("global")->error() << "VScriptSubsystem::DisconnectAllIncomingActivations() not implemented";
    }

    /**
     * Removes all outgoing and incoming activations.
     */
    void VScriptSubsystem::DisconnectAllActivations(InstanceRefPtr<EntityInstance> entity)
    {
    	// TODO: implement
    	spdlog::get("global")->error() << "VScriptSubsystem::DisconnectAllActivations() not implemented";
    }

}
}
