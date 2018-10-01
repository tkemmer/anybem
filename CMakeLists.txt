cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(AnyBEM CXX)

#######################################################################################################################
# Dependencies

## AnyDSL
find_package(AnyDSL_runtime REQUIRED)

## Badhron
find_package(Badhron)

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
include_directories(include)
include_directories(SYSTEM ${CLIPP_INCLUDE_DIR})

set(AnyBEM_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-Wall -pedantic -fsanitize=address")
	list(APPEND AnyBEM_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

set(AnyBEM_IMPALA_FILES
	src/impala/backend/backend_cpu.impala
	src/impala/import.impala
	src/impala/types.impala
	src/impala/constants.impala
	src/impala/model.impala
	src/impala/linalg.impala
	src/impala/rjasanow.impala
	src/impala/born.impala
	src/impala/export.impala
)

set(AnyBEM_SOURCE_FILES
	include/anybem/error.h
	include/anybem/hmo_reader.h
	include/anybem/impala.h
	include/anybem/model.h
	include/anybem/reader.h
	include/anybem/types.h
	include/anybem/util.h
	src/cpp/hmo_reader.cpp
	src/cpp/util.cpp
)


#######################################################################################################################
# AnyBEM
anydsl_runtime_wrap(AnyBEM_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	${AnyBEM_IMPALA_FILES}
)

add_executable(anybem
	${AnyBEM_PROGRAM}
	${AnyBEM_SOURCE_FILES}
	src/cpp/main.cpp
)

target_link_libraries(anybem ${AnyDSL_runtime_LIBRARIES} ${Badhron_LIBRARIES})
set_target_properties(anybem PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)


#######################################################################################################################
# AnyBEM tests
if(Badhron_FOUND)
	anydsl_runtime_wrap(AnyBEM_TEST_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
		${Badhron_IMPALA_FILES}
		${AnyBEM_IMPALA_FILES}
		test/linalg.impala
		test/rjasanow.impala
		test/main.impala
	)

	add_executable(anybem_test
		${AnyBEM_TEST_PROGRAM}
		${AnyBEM_SOURCE_FILES}
		test/main.cpp
	)

	target_link_libraries(anybem_test ${AnyDSL_runtime_LIBRARIES} ${Badhron_LIBRARIES})
	set_target_properties(anybem_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

else()
	message(STATUS "Badhron has not been found. Disabling AnyBEM test suite.")
endif()
