cmake_minimum_required(VERSION 3.12...3.14)

project(AnyBEM
	VERSION      0.1
	DESCRIPTION  "Nonlocal Protein Electrostatics in Impala"
	HOMEPAGE_URL "https://github.com/tkemmer/anybem"
	LANGUAGES    CXX
)

# Dependencies
find_package(AnyDSL_runtime REQUIRED)

# Default properties for all targets
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(include)

set(AnyBEM_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND AnyBEM_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

add_subdirectory(src)
add_subdirectory(tools/cli)

# Tests
include(CTest)
if(BUILD_TESTING)
	add_subdirectory(test)
endif()
