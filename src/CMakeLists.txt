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
set(AnyBEM_SOURCE_FILES ${AnyBEM_SOURCE_FILES} PARENT_SCOPE)

anydsl_runtime_wrap(AnyBEM_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	${AnyBEM_IMPALA_FILES}
)

add_executable(anybem
	${AnyBEM_PROGRAM}
	${AnyBEM_SOURCE_FILES}
	cpp/main.cpp
)
target_link_libraries(anybem ${AnyDSL_runtime_LIBRARIES})
