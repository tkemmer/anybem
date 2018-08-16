#include "types.h"

extern "C" {
	void anybem_node_buffer_stats(anybem::NodeBuffer::Prototype* nodes);
	void anybem_surface_element_buffer_stats(anybem::TriangleBuffer::Prototype* elements);
	void anybem_charge_buffer_stats(anybem::ChargeBuffer::Prototype* charges);
	void anybem_surface_model_stats(anybem::SurfaceModel::Prototype* surf);
}
