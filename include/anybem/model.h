#ifndef ANYBEM_MODEL_H
#define ANYBEM_MODEL_H

#include <anybem/types.h>

#include <vector>

namespace anybem {

	// ================================================================================================================
	// Elements

	struct TrianglePrimitive {
		Position v1;
		Position v2;
		Position v3;
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
			SurfaceElementBuffer::Prototype elements;
			ChargeBuffer::Prototype         charges;
			SystemParams                    params;
		};

		explicit SurfaceModel(SurfaceElementBuffer&& elements) :
			elements_{std::move(elements)},
			charges_{},
			params_{default_params} {
		}

		SurfaceModel(
			SurfaceElementBuffer&& elements,
			ChargeBuffer&& charges
		) :
			elements_{std::move(elements)},
			charges_{std::move(charges)},
			params_{default_params} {
		}

		SurfaceModel(SurfaceModel&&) = default;
		SurfaceModel& operator=(SurfaceModel&&) = default;

		~SurfaceModel() = default;

		Prototype prototype() {
			return {
				elements_.prototype(),
				charges_.prototype(),
				params_
			};
		}

		void charges(ChargeBuffer&& charges) noexcept { charges_ = std::move(charges); }
		void params(SystemParams params) noexcept { params_ = params; }

		index_t element_count() const noexcept { return elements_.size(); }
		index_t charge_count() const noexcept { return charges_.size(); }

	private:
		SurfaceElementBuffer elements_;
		ChargeBuffer         charges_;
		SystemParams         params_;
	};
}

#endif // ANYBEM_MODEL_H
