set(TEST_BINARY unit_tests CACHE INTERNAL "")

declare_module(test .)

# This needs to come before the target, sigh
link_directories(${GTEST_LIB_DIR})

add_app(${TEST_BINARY} ${TEST_MODULE_SOURCES} CONSOLE_APP)

require_util(${TEST_BINARY})
require_gtest(${TEST_BINARY})

target_link_libraries(${TEST_BINARY} ${ADDITIONAL_LIBRARIES})

add_custom_target(run_tests COMMAND $<TARGET_FILE:${TEST_BINARY}>)
