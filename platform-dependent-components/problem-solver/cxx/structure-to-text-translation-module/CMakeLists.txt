set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE ALL_SOURCES ${ROOT_DIR}/*.cpp)
file(GLOB_RECURSE ALL_HEADERS ${ROOT_DIR}/*.hpp)
# Exclude files in the 'test' folder
file(GLOB_RECURSE TEST_FILES ${ROOT_DIR}/test/*)
list(REMOVE_ITEM ALL_SOURCES ${TEST_FILES})
list(REMOVE_ITEM ALL_HEADERS ${TEST_FILES})
# Set the SOURCE variable
set(SOURCES ${ALL_SOURCES})
set(HEADERS ${ALL_HEADERS})

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${LOCAL_COMMON_MODULE_PATH}
    	${COMMON_MODULE_PATH})

add_library(translationModule SHARED ${SOURCES} ${HEADERS})

target_link_libraries(translationModule sc-memory sc-agents-common local-common)

sc_codegen_ex(translationModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${HCARE_CLANG_FORMAT_CODE})
	target_clangformat_setup(translationModule)
endif()

if (${SC_BUILD_TESTS})
	include(${CMAKE_CURRENT_LIST_DIR}/test/tests.cmake)
endif ()
