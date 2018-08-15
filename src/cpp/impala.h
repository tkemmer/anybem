#include "types.h"

extern "C" {
	void anybem_node_buffer_stats(anybem::Node* nodes, anybem::index_t len);
	void anybem_surface_element_buffer_stats(anybem::Triangle* elements, anybem::index_t len);
	void anybem_charge_buffer_stats(anybem::Charge* charges, anybem::index_t len);
}
