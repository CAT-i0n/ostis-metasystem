set(SOURCES
		"TranslationModule.cpp"
		"agent/SubstructuresToTextTranslationAgent.cpp"
		"agent/StructureSubdividingAgent.cpp"
		"eraser/TranslationEraser.cpp"
		"constants/TranslationConstants.cpp"
		"generator/TranslationGenerator.cpp"
		"handler/TranslationHandler.cpp"
		"keynodes/TranslationKeynodes.cpp"
		"manager/SubstructuresToTextTranslationManager.cpp"
		"manager/StructureSubdividingManager.cpp"
		"searcher/TranslationSearcher.cpp"
		"templates/TranslationTemplates.cpp"
		)

set(HEADERS
		"TranslationModule.hpp"
		"agent/SubstructuresToTextTranslationAgent.hpp"
		"agent/StructureSubdividingAgent.hpp"
		"eraser/TranslationEraser.hpp"
		"constants/TranslationConstants.hpp"
		"generator/TranslationGenerator.hpp"
		"handler/TranslationHandler.hpp"
		"keynodes/TranslationKeynodes.hpp"
		"manager/SubstructuresToTextTranslationManager.hpp"
		"manager/StructureSubdividingManager.hpp"
		"searcher/TranslationSearcher.hpp"
		"templates/TranslationTemplates.hpp"
		)

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
