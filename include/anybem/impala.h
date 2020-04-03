#ifndef ANYBEM_IMPALA_H
#define ANYBEM_IMPALA_H

#include <anybem/model.h>

extern "C" {
	void anybem_surface_model_stats(const anybem::SurfaceModel::Primitive* surf);
}

#endif // ANYBEM_IMPALA_H
