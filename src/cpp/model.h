#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include "types.h"

namespace anybem {
	struct Triangle {
		index_t    v1;       // first node
		index_t    v2;       // second node
		index_t    v3;       // third node
		position_t center;   // centroid
		position_t normal;   // unit normal vector
		real_t     area;     // surface area
		real_t     dist;     // distance to origin
	};

	struct Charge {
		position_t pos;
		real_t     val;
	};
}

#endif // ANYBEM_MODEL_H
