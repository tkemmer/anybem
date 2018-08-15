#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include "types.h"

#include <vector>

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

	class SurfaceModelResource final {
	public:
		SurfaceModelResource(
			std::vector<Node>&& nodes,
			std::vector<SurfaceElement>&& elements,
			std::vector<Charge>&& charges
		) :
			nodes_{nodes},
			elements_{elements},
			charges_{charges} {
		}

		~SurfaceModelResource() = default;

		SurfaceModel get() {
			return SurfaceModel{
				nodes_.data(),
				elements_.data(),
				charges_.data(),
				{0, 0, 0, 0} // TODO
			};
		}

		std::vector<Node>::size_type node_count() { return nodes_.size(); }
		std::vector<SurfaceElement>::size_type element_count() { return elements_.size(); }
		std::vector<Charge>::size_type charge_count() { return charges_.size(); }

	private:
		std::vector<Node>           nodes_;
		std::vector<SurfaceElement> elements_;
		std::vector<Charge>         charges_;
	};
}

#endif // ANYBEM_MODEL_H
