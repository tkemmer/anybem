#ifndef ANYBEM_HMO_READER_H
#define ANYBEM_HMO_READER_H

#include "model.h"

#include <memory>
#include <string>
#include <vector>

namespace anybem {

	/**
	 * HMO file reader for surface models (including charges).
	 *
	 * This file format is somewhat ancient and the only source for the format specification - to the best of my
	 * knowledge - is https://espace.cern.ch/roxie/Documentation/ironFileDoc.pdf.
	 */
	class HMOReader final {
	public:
		/**
		 * Reads the surface model and charges from the given file.
		 *
		 * @param filename path to an HMO file
		 * @throws FileAccessError if the given file is not readable
		 * @throws FileFormatError if the given HMO file is corrupt or unsupported
		 */
		explicit HMOReader(const std::string& filename);
		~HMOReader() noexcept;

		HMOReader(const HMOReader&) = delete;
		HMOReader(const HMOReader&&) = delete;
		HMOReader& operator=(const HMOReader&) = delete;
		HMOReader& operator=(const HMOReader&&) = delete;

		std::vector<position_t>& nodes() noexcept;
		std::vector<Triangle>& elements() noexcept;
		std::vector<Charge>& charges() noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> impl_;
	};

}

#endif // ANYBEM_HMO_READER
