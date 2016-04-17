set(TEST_BINARY unit_tests CACHE INTERNAL "")

declare_module(test .)

# This needs to come before the target, sigh
link_directories(${GTEST_LIB_DIR})

add_app(${TEST_BINARY} ${TEST_MODULE_SOURCES} CONSOLE_APP)

config_net(${TEST_BINARY})
config_util(${TEST_BINARY})
config_gtest(${TEST_BINARY})
config_cxx11_abi(${TEST_BINARY})

target_link_libs(${TEST_BINARY} ${ADDITIONAL_LIBRARIES})

add_custom_target(run_tests COMMAND $<TARGET_FILE:${TEST_BINARY}>)
