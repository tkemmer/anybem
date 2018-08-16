#ifndef ANYBEM_IMPALA_H
#define ANYBEM_IMPALA_H

#include "model.h"

extern "C" {
	void anybem_node_buffer_stats(const anybem::NodeBuffer::Prototype* nodes);
	void anybem_surface_element_buffer_stats(const anybem::TriangleBuffer::Prototype* elements);
	void anybem_charge_buffer_stats(const anybem::ChargeBuffer::Prototype* charges);
	void anybem_surface_model_stats(const anybem::SurfaceModel::Prototype* surf);
}

#endif // ANYBEM_IMPALA_H
