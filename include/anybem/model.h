#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include <anybem/types.h>

#include <vector>

namespace anybem {

	// ================================================================================================================
	// Nodes

	using NodePrimitive = Position;

	class NodeBuffer final {
	public:
		struct Prototype {
			NodePrimitive* data;
			index_t        len;
		};

		explicit NodeBuffer(std::vector<NodePrimitive>&& nodes) :
			nodes_{nodes} {
		}

		NodeBuffer(NodeBuffer&&) = default;
		NodeBuffer& operator=(NodeBuffer&&) = default;

		~NodeBuffer() noexcept = default;

		Prototype prototype() { return {nodes_.data(), size()}; }

		index_t size() const noexcept { return nodes_.size(); }

	private:
		std::vector<NodePrimitive> nodes_;
	};


	// ================================================================================================================
	// Elements

	struct TrianglePrimitive {
		index_t v1;   // index of first node in node buffer
		index_t v2;   // index of second node in node buffer
		index_t v3;   // index of third node in node buffer
	};

	class TriangleBuffer final {
	public:
		struct Prototype {
			TrianglePrimitive* data;
			index_t            len;
		};

		explicit TriangleBuffer(std::vector<TrianglePrimitive>&& elements) :
			elements_{elements} {
		}

		TriangleBuffer(TriangleBuffer&&) = default;
		TriangleBuffer& operator=(TriangleBuffer&&) = default;

		~TriangleBuffer() noexcept = default;

		Prototype prototype() { return {elements_.data(), size()}; }

		index_t size() const noexcept { return elements_.size(); }

	private:
		std::vector<TrianglePrimitive> elements_;
	};

	using SurfaceElementPrimitive = TrianglePrimitive;
	using SurfaceElementBuffer = TriangleBuffer;


	// ================================================================================================================
	// Charges

	struct ChargePrimitive {
		Position pos;
		real_t   val;
	};

	class ChargeBuffer final {
	public:
		struct Prototype {
			ChargePrimitive* data;
			index_t          len;
		};

		ChargeBuffer() :
			charges_{} {
		}

		explicit ChargeBuffer(std::vector<ChargePrimitive>&& charges) :
			charges_{charges} {
		}

		ChargeBuffer(ChargeBuffer&&) = default;
		ChargeBuffer& operator=(ChargeBuffer&&) = default;

		~ChargeBuffer() noexcept = default;

		Prototype prototype() { return {charges_.data(), size()}; }

		index_t size() const noexcept { return charges_.size(); }

	private:
		std::vector<ChargePrimitive> charges_;
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
			ChargeBuffer::Prototype         charges;
			SystemParams                    params;
		};

		SurfaceModel(NodeBuffer&& nodes, SurfaceElementBuffer&& elements) :
			nodes_{std::move(nodes)},
			elements_{std::move(elements)},
			charges_{},
			params_{default_params} {
		}

		SurfaceModel(
			NodeBuffer&& nodes,
			SurfaceElementBuffer&& elements,
			ChargeBuffer&& charges
		) :
			nodes_{std::move(nodes)},
			elements_{std::move(elements)},
			charges_{std::move(charges)},
			params_{default_params} {
		}

		SurfaceModel(SurfaceModel&&) = default;
		SurfaceModel& operator=(SurfaceModel&&) = default;

		~SurfaceModel() = default;

		Prototype prototype() {
			return {
				nodes_.prototype(),
				elements_.prototype(),
				charges_.prototype(),
				params_
			};
		}

		void charges(ChargeBuffer&& charges) noexcept { charges_ = std::move(charges); }
		void params(SystemParams params) noexcept { params_ = params; }

		index_t node_count() const noexcept { return nodes_.size(); }
		index_t element_count() const noexcept { return elements_.size(); }
		index_t charge_count() const noexcept { return charges_.size(); }

	private:
		NodeBuffer           nodes_;
		SurfaceElementBuffer elements_;
		ChargeBuffer         charges_;
		SystemParams         params_;
	};
}

#endif // ANYBEM_MODEL_H