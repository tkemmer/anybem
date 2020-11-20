cmake_minimum_required(VERSION 3.12...3.16)

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
#set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(include)
include_directories("${PROJECT_BINARY_DIR}/include")

set(AnyBEM_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND AnyBEM_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

set(AnyBEM_BACKEND "cpu" CACHE STRING "Back end to be used for matrix multiplication: cpu or cuda")
set(AnyBEM_PLATFORM "acc")
if(AnyBEM_BACKEND STREQUAL "cpu")
	set(AnyBEM_PLATFORM "cpu")
endif()

set(AnyBEM_DEVICE 0 CACHE STRING "ID of device to be used with accelerator-based back ends (e.g., CUDA): 0 (default)")

set(AnyBEM_INTRINSICS "f64" CACHE STRING "Floating-point precision level for intrinsics: f32 or f64")
if(AnyBEM_INTRINSICS STREQUAL "f32")
	set(AnyBEM_FTYPE "float")
else()
	set(AnyBEM_FTYPE "double")
endif()

add_subdirectory(src)
add_subdirectory(tools/cli)

# Tests
include(CTest)
if(BUILD_TESTING)
	add_subdirectory(test)
endif()
