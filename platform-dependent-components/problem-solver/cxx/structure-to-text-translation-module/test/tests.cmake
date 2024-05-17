make_tests_from_folder(${CMAKE_CURRENT_LIST_DIR}/units
		NAME translation_test_starter
		DEPENDS sc-agents-common translationModule sc-builder-lib local-common boost_filesystem sc-core
		INCLUDES ${SC_MEMORY_SRC}/tests/sc-memory/_test ${CMAKE_CURRENT_LIST_DIR}/.. ${SC_MACHINE_ROOT}/sc-tools/sc-builder/src)

add_definitions(-DTEST_SRC_PATH="${CMAKE_CURRENT_LIST_DIR}")
