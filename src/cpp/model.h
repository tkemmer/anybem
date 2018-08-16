#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include "types.h"

#include <vector>

namespace anybem {

	// ================================================================================================================
	// Nodes

	using Node = position_t;

	class NodeBuffer final {
	public:
		struct Prototype {
			Node*   data;
			index_t len;
		};

		explicit NodeBuffer(std::vector<Node>&& nodes) :
			nodes_{nodes} {
		}

		~NodeBuffer() noexcept = default;

		Prototype prototype() { return {nodes_.data(), size()}; }

		index_t size() const noexcept { return nodes_.size(); }

	private:
		std::vector<Node> nodes_;
	};


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

	class TriangleBuffer final {
	public:
		struct Prototype {
			Triangle* data;
			index_t   len;
		};

		explicit TriangleBuffer(std::vector<Triangle>&& elements) :
			elements_{elements} {
		}

		~TriangleBuffer() noexcept = default;

		Prototype prototype() { return {elements_.data(), size()}; }

		index_t size() const noexcept { return elements_.size(); }

	private:
		std::vector<Triangle> elements_;
	};

	using SurfaceElement = Triangle;
	using SurfaceElementBuffer = TriangleBuffer;


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
			NodeBuffer::Prototype           nodes;
			SurfaceElementBuffer::Prototype elements;
			Charge*                         charges;
			index_t                         charge_count;
			SystemParams                    params;
		};

		SurfaceModel(NodeBuffer&& nodes, SurfaceElementBuffer && elements) :
			nodes_{nodes},
			elements_{elements},
			charges_{},
			params_{default_params} {
		}

		SurfaceModel(
			NodeBuffer&& nodes,
			SurfaceElementBuffer && elements,
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
				nodes_.prototype(),
				elements_.prototype(),
				charges_.data(),
				charge_count(),
				params_
			};
		}

		void charges(std::vector<Charge>&& charges) noexcept { charges_ = std::move(charges); }
		void params(SystemParams params) noexcept { params_ = params; }

		index_t node_count() const noexcept { return nodes_.size(); }
		index_t element_count() const noexcept { return elements_.size(); }
		index_t charge_count() const noexcept { return charges_.size(); }

	private:
		NodeBuffer           nodes_;
		SurfaceElementBuffer elements_;
		std::vector<Charge>  charges_;
		SystemParams         params_;
	};
}

#endif // ANYBEM_MODEL_H
