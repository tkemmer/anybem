find_package(Badhron REQUIRED)

anydsl_runtime_wrap(AnyBEM_TEST_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	${Badhron_IMPALA_FILES}
	${AnyBEM_IMPALA_FILES}
	"badhron_${AnyBEM_INTRINSICS}.impala"
	math.impala
	yukawa.impala
	laplace.impala
	runtests.impala
)

add_executable(anybem_test
	${AnyBEM_TEST_PROGRAM}
	runtests.cpp
)
target_link_libraries(anybem_test libanybem badhron)
