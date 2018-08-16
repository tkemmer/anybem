#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include "types.h"

#include <vector>

namespace anybem {

	// ================================================================================================================
	// Nodes

	using Node = position_t;


	// ================================================================================================================
	// Elements
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


	// ================================================================================================================
	// Charges

	struct Charge {
		position_t pos;
		real_t     val;
	};


	// ================================================================================================================
	// System parameters

	struct SystemParams {
		real_t epsOmega;
		real_t epsSigma;
		real_t epsInf;
		real_t lambda;
	};

	constexpr SystemParams default_params = {2, 78, 1.8, 20};


	// ================================================================================================================
	// Surface model

	class SurfaceModel final {
	public:

		struct Prototype {
			Node*           nodes;
			index_t         node_count;
			SurfaceElement* elements;
			index_t         element_count;
			Charge*         charges;
			index_t         charge_count;
			SystemParams    params;
		};

		SurfaceModel(std::vector<Node>&& nodes, std::vector<SurfaceElement>&& elements) :
			nodes_{nodes},
			elements_{elements},
			charges_{},
			params_{default_params} {
		}

		SurfaceModel(
			std::vector<Node>&& nodes,
			std::vector<SurfaceElement>&& elements,
			std::vector<Charge>&& charges
		) :
			nodes_{nodes},
			elements_{elements},
			charges_{charges},
			params_{default_params} {
		}

		~SurfaceModel() = default;

		Prototype prototype() {
			return {
				nodes_.data(),
				node_count(),
				elements_.data(),
				element_count(),
				charges_.data(),
				charge_count(),
				params_
			};
		}

		void charges(std::vector<Charge>&& charges) noexcept { charges_ = std::move(charges); }
		void params(SystemParams params) noexcept { params_ = params; }

		index_t node_count() const { return nodes_.size(); }
		index_t element_count() const { return elements_.size(); }
		index_t charge_count() const { return charges_.size(); }

	private:
		std::vector<Node>           nodes_;
		std::vector<SurfaceElement> elements_;
		std::vector<Charge>         charges_;
		SystemParams                params_;
	};
}

#endif // ANYBEM_MODEL_H
