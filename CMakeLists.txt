cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(AnyBEM CXX)

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
		COMMAND ${GIT_CMD} submodule update --init -- deps/clipp
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_QUIET
	)
endif()


#######################################################################################################################
# Project configuration
include_directories(src/cpp)
include_directories(SYSTEM ${CLIPP_INCLUDE_DIR})

set(AnyBEM_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND AnyBEM_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

anydsl_runtime_wrap(AnyBEM_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	src/impala/backend/backend_cpu.impala
	src/impala/import.impala
	src/impala/types.impala
	src/impala/constants.impala
	src/impala/model.impala
	src/impala/util.impala
	src/impala/born.impala
	src/impala/export.impala
)

add_executable(anybem
	${AnyBEM_PROGRAM}
	src/cpp/error.h
	src/cpp/hmo_reader.h
	src/cpp/hmo_reader.cpp
	src/cpp/impala.h
	src/cpp/main.cpp
	src/cpp/model.h
	src/cpp/types.h
	src/cpp/util.h
	src/cpp/util.cpp
)

target_link_libraries(anybem ${AnyDSL_runtime_LIBRARIES})
set_target_properties(anybem PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
