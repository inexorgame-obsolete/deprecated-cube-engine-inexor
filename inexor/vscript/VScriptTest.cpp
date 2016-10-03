#include "VScriptTest.hpp"

namespace inexor {
namespace vscript {

    VScriptTest::VScriptTest(std::shared_ptr<EntitySystem> entity_system)
      : entity_system(entity_system)
    {
        type_event_on_memory_changed = entity_system->GetEntityTypeManager()->Get(ENT_TYPE_EVENT_ON_MEMORY_CHANGED);
        // memory_integer_type = entity_system->GetEntityTypeManager()->Get(ENT_TYPE_MEMORY_INTEGER);
        // operator_add_type = entity_system->GetEntityTypeManager()->Get(ENT_TYPE_OPERATOR_ADD);
        // action_print_type = entity_system->GetEntityTypeManager()->Get(ENT_TYPE_ACTION_PRINT);
    }

    VScriptTest::~VScriptTest()
    {
    }

    void VScriptTest::RunTests()
    {
    	SubsystemTest();
    }

    void VScriptTest::SubsystemTest()
    {
        spdlog::get("global")->info() << "Try to access vscript subsystem by type";
        std::shared_ptr<inexor::vscript::VScriptSubsystem> vscript_subsystem = entity_system->GetSubsystem<inexor::vscript::VScriptSubsystem>();
        TimeStep time_step(100.0, 1000.0);
        vscript_subsystem->Update(time_step);

        InstanceRefPtr<EntityInstance> on_memory_changed_1 = vscript_subsystem->GetEventManager()->CreateEvent(type_event_on_memory_changed, 512.0, 512.0, 550.0);

        InstanceRefPtr<EntityInstance> print_1 = vscript_subsystem->GetActionManager()->CreateAction(type_action_print, 512.0, 550.0, 550.0);

        InstanceRefPtr<EntityInstance> print_2 = vscript_subsystem->GetActionManager()->CreateAction(type_action_print, 512.0, 650.0, 550.0);

        vscript_subsystem->GetEventManager()->Connect(on_memory_changed_1, print_1);
        vscript_subsystem->GetActionManager()->Connect(print_1, print_2);

        /*

        spdlog::get("global")->info() << "Test timer to memory";

        // Creates and initializes two timer events

        InstanceRefPtr<EntityInstance> timer_event_1 = vscript_subsystem->CreateEvent(event_timer_type, 512.0, 512.0, 550.0);
        timer_event_1["name"] = "timer_1";
        timer_event_1["rate"] = 250;

        // Creates and initializes two integer memory entities

        InstanceRefPtr<EntityInstance> integer_memory_1 = vscript_subsystem->CreateMemory(memory_integer_type, 612.0, 512.0, 550.0, false);
        integer_memory_1["value"] = 0;

        InstanceRefPtr<EntityInstance> integer_memory_2 = vscript_subsystem->CreateMemory(memory_integer_type, 612.0, 612.0, 550.0, false);
        integer_memory_2["value"] = 100;

        InstanceRefPtr<EntityInstance> add_operator_1 = vscript_subsystem->CreateOperator(operator_add_type, 612.0, 612.0, 550.0, false);

        InstanceRefPtr<EntityInstance> print_action_1 = vscript_subsystem->CreateAction(action_print_type, 612.0, 612.0, 550.0, false);

        // Connect the timers with the memory entities
        vscript_subsystem->ConnectActivation(timer_event_1, print_action_1);
        vscript_subsystem->ConnectActivation(integer_memory_1, add_operator_1);
        vscript_subsystem->ConnectActivation(integer_memory_2, add_operator_1);
        vscript_subsystem->ConnectActivation(add_operator_1, print_action_1);
        */

    }

}
}
