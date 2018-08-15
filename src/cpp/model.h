#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include "types.h"

namespace anybem {

	using Node = position_t;

	struct Triangle {
		index_t    v1;       // first node
		index_t    v2;       // second node
		index_t    v3;       // third node
		position_t center;   // centroid
		position_t normal;   // unit normal vector
		real_t     area;     // surface area
		real_t     dist;     // distance to origin
	};

	using SurfaceElement = Triangle;

	struct Charge {
		position_t pos;
		real_t     val;
	};

	struct SystemParams {
		real_t epsOmega;
		real_t epsSigma;
		real_t epsInf;
		real_t lambda;
	};

	struct SurfaceModel {
		Node*           nodes;
		SurfaceElement* elements;
		Charge*         charges;
		SystemParams    params;
	};
}

#endif // ANYBEM_MODEL_H
