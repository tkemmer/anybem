#ifndef ANYBEM_HMO_READER_H
#define ANYBEM_HMO_READER_H

#include "model.h"

#include <memory>
#include <string>
#include <vector>

namespace anybem {

	class HMOReader final {
	public:
		explicit HMOReader(const std::string& filename);
		~HMOReader() noexcept;

		HMOReader(const HMOReader&) = delete;
		HMOReader(const HMOReader&&) = delete;
		HMOReader& operator=(const HMOReader&) = delete;
		HMOReader& operator=(const HMOReader&&) = delete;

		std::vector<position_t>& getNodes() noexcept;
		std::vector<Triangle>& getElements() noexcept;
		std::vector<Charge>& getCharges() noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> impl_;
	};

}

#endif // ANYBEM_HMO_READER
