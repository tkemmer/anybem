#ifndef ANYBEM_IMPALA_H
#define ANYBEM_IMPALA_H

#include <anybem/model.h>

extern "C" {
	void anybem_surface_model_stats(const anybem::SurfaceModel::Primitive* surf);
	void anybem_bench_matvec(const anybem::SurfaceModel::Primitive* model, int32_t);
}

#endif // ANYBEM_IMPALA_H
