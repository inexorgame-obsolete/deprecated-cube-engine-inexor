set(TEST_BINARY testcmd CACHE INTERN "")

declare_module(test .)

# This needs to come before the target, sigh
link_directories(${GTEST_LIB_DIR})

add_app(${TEST_BINARY} ${TEST_MODULE_SOURCES})

config_net(${TEST_BINARY})
config_util(${TEST_BINARY})
config_gtest(${TEST_BINARY})

target_link_libs(${TEST_BINARY} ${ADDITIONAL_LIBRARIES})

add_custom_target(run_tests COMMAND $<TARGET_FILE:${TEST_BINARY}>)
