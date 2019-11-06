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
set(AnyBEM_IMPALA_FILES ${AnyBEM_IMPALA_FILES} PARENT_SCOPE)

anydsl_runtime_wrap(AnyBEM_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	${AnyBEM_IMPALA_FILES}
)

add_library(libanybem SHARED
	${AnyBEM_PROGRAM}
	../include/anybem/error.h
	../include/anybem/hmo_reader.h
	../include/anybem/impala.h
	../include/anybem/model.h
	../include/anybem/reader.h
	../include/anybem/types.h
	../include/anybem/util.h
	cpp/hmo_reader.cpp
	cpp/util.cpp
)
target_link_libraries(libanybem PUBLIC ${AnyDSL_runtime_LIBRARIES})
