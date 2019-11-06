find_package(Badhron REQUIRED)

anydsl_runtime_wrap(AnyBEM_TEST_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	${Badhron_IMPALA_FILES}
	${AnyBEM_IMPALA_FILES}
	linalg.impala
	radon.impala
	rjasanow.impala
	runtests.impala
)

add_executable(anybem_test
	${AnyBEM_TEST_PROGRAM}
	${AnyBEM_SOURCE_FILES}
	runtests.cpp
)

target_link_libraries(anybem_test badhron)
