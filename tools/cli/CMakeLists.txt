find_package(clipp REQUIRED)

add_executable(anybem
	main.cpp
)
target_link_libraries(anybem libanybem clipp::clipp)
