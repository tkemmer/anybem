cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(AnyBEM CXX)

find_package(AnyDSL_runtime REQUIRED)
include_directories(${ANYDSL_RUNTIME_DIR}/src)

include_directories(src/cpp)

anydsl_runtime_wrap(AnyBEM_PROGRAM  FILES
	src/impala/types.impala
	src/impala/constants.impala
	src/impala/model.impala
	src/impala/util.impala
	src/impala/born.impala
	src/impala/main.impala
)

add_executable(anybem
	${AnyBEM_PROGRAM}
	src/cpp/main.h
	src/cpp/main.cpp
)

target_link_libraries(anybem ${ANYDSL_RUNTIME_LIBRARY} ${ANYDSL_RUNTIME_LIBRARIES})
set_target_properties(anybem PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
