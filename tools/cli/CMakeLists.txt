# Dependency: clipp
set(CLIPP_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/clipp/include" CACHE INTERNAL "Clipp include directory")
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${CLIPP_INCLUDE_DIR}")
	message(STATUS "Fetching dependency Clipp")
	find_program(GIT_CMD git REQUIRED)
	execute_process(
		COMMAND "${GIT_CMD}" submodule update --init -- deps/clipp
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
		OUTPUT_QUIET
	)
endif()

add_executable(anybem
	${CLIPP_INCLUDE_DIR}
	main.cpp
)
target_link_libraries(anybem libanybem)
