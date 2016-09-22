#include "VScriptTest.hpp"

namespace inexor {
namespace vscript {

    VScriptTest::VScriptTest(std::shared_ptr<EntitySystem> entity_system)
      : entity_system(entity_system)
    {
        timer_event_type = entity_system->GetEntityTypeManager()->Get(ENT_TIMER_EVENT);
        integer_memory_type = entity_system->GetEntityTypeManager()->Get(ENT_INTEGER_MEMORY);
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

        spdlog::get("global")->info() << "Test timer to memory";

        // Creates and initializes two timer events
        InstanceRefPtr<EntityInstance> timer_event_1 = vscript_subsystem->CreateEvent(timer_event_type, 512.0, 512.0, 550.0);
        timer_event_1["rate"] = 250;
        InstanceRefPtr<EntityInstance> timer_event_2 = vscript_subsystem->CreateEvent(timer_event_type, 512.0, 512.0, 550.0);
        timer_event_2["rate"] = 350;

        // Creates and initializes a integer memory
        InstanceRefPtr<EntityInstance> integer_memory_1 = vscript_subsystem->CreateMemory(integer_memory_type, 512.0, 512.0, 550.0, false);
        integer_memory_1["value"] = 0;

        // Connect the timers with the memory entities
        vscript_subsystem->ConnectActivation(timer_event_1, integer_memory_1, ENT_FUNC_INCREASE_INTEGER);
        vscript_subsystem->ConnectActivation(timer_event_2, integer_memory_1, ENT_FUNC_DECREASE_INTEGER);

    }

}
}
