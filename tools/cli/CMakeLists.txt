find_package(clipp REQUIRED)

get_target_property(CLIPP_INCLUDE_DIRS clipp::clipp INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${CLIPP_INCLUDE_DIRS})

add_executable(anybem-cli
	main.cpp
)
target_link_libraries(anybem-cli anybem)
