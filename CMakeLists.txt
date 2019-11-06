cmake_minimum_required(VERSION 3.12...3.14)

project(AnyBEM
	VERSION      0.1
	DESCRIPTION  "Nonlocal Protein Electrostatics in Impala"
	HOMEPAGE_URL "https://github.com/tkemmer/anybem"
	LANGUAGES    CXX
)

#######################################################################################################################
# Dependencies

## AnyDSL
find_package(AnyDSL_runtime REQUIRED)

## Clipp
set(CLIPP_INCLUDE_DIR "deps/clipp/include" CACHE INTERNAL "Clipp include directory")
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${CLIPP_INCLUDE_DIR}")
	message(STATUS "Fetching dependency Clipp")
	find_program(GIT_CMD git REQUIRED)
	execute_process(
		COMMAND "${GIT_CMD}" submodule update --init -- deps/clipp
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_QUIET
	)
endif()

#######################################################################################################################
# Project configuration
include_directories(include)
include_directories(SYSTEM "${CLIPP_INCLUDE_DIR}")

# Default properties for all targets
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AnyBEM_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-Wall -pedantic -fsanitize=address")
	list(APPEND AnyBEM_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

add_subdirectory(src)

# Tests
include(CTest)
if(BUILD_TESTING)
	add_subdirectory(test)
endif()
