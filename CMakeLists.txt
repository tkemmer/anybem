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

## Badhron
find_package(Badhron)

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

set(AnyBEM_IMPALA_FILES
	"${PROJECT_SOURCE_DIR}/src/impala/backend/backend_cpu.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/import.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/types.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/constants.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/model.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/linalg.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/radon.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/rjasanow.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/born.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/export.impala"
)

set(AnyBEM_SOURCE_FILES
	"${PROJECT_SOURCE_DIR}/include/anybem/error.h"
	"${PROJECT_SOURCE_DIR}/include/anybem/hmo_reader.h"
	"${PROJECT_SOURCE_DIR}/include/anybem/impala.h"
	"${PROJECT_SOURCE_DIR}/include/anybem/model.h"
	"${PROJECT_SOURCE_DIR}/include/anybem/reader.h"
	"${PROJECT_SOURCE_DIR}/include/anybem/types.h"
	"${PROJECT_SOURCE_DIR}/include/anybem/util.h"
	"${PROJECT_SOURCE_DIR}/src/cpp/hmo_reader.cpp"
	"${PROJECT_SOURCE_DIR}/src/cpp/util.cpp"
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
		test/radon.impala
		test/rjasanow.impala
		test/runtests.impala
	)

	add_executable(anybem_test
		${AnyBEM_TEST_PROGRAM}
		${AnyBEM_SOURCE_FILES}
		test/runtests.cpp
	)

	target_link_libraries(anybem_test ${Badhron_LIBRARIES})
	set_target_properties(anybem_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

else()
	message(STATUS "Badhron has not been found. Disabling AnyBEM test suite.")
endif()
