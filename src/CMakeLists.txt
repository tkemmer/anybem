set(AnyBEM_IMPALA_FILES
	"${PROJECT_SOURCE_DIR}/src/impala/backend/backend_${AnyBEM_BACKEND}.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/intrinsics/intrinsics_${AnyBEM_INTRINSICS}.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/platform/matrix_${AnyBEM_PLATFORM}.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/import.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/common.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/math.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/model.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/yukawa.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/laplace.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/matrix.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/local.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/nonlocal.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/born.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/export.impala"
)
set(AnyBEM_IMPALA_FILES ${AnyBEM_IMPALA_FILES} PARENT_SCOPE)

anydsl_runtime_wrap(AnyBEM_PROGRAM IMPALA_FLAGS ${AnyBEM_IMPALA_FLAGS} FILES
	${AnyBEM_IMPALA_FILES}
)

configure_file("../include/anybem/types.h.in" "${PROJECT_BINARY_DIR}/include/anybem/types.h")

add_library(libanybem SHARED
	${AnyBEM_PROGRAM}
	../include/anybem/error.h
	../include/anybem/hmo_reader.h
	../include/anybem/impala.h
	../include/anybem/model.h
	../include/anybem/reader.h
	"${PROJECT_BINARY_DIR}/include/anybem/types.h"
	../include/anybem/util.h
	cpp/hmo_reader.cpp
	cpp/util.cpp
)
target_link_libraries(libanybem PUBLIC ${AnyDSL_runtime_LIBRARIES})
