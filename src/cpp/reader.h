#ifndef ANYBEM_READER_H
#define ANYBEM_READER_H

#include "model.h"

#include <string>

namespace anybem {

	class Reader {
	public:
		Reader() = default;
		virtual ~Reader() noexcept = default;

		/**
		 * Indicates whether the models generated from this reader contain charges. This can be either a limitation of
		 * the specific reader or the underlying file format. If charges are not supported, the charge list in the
		 * corresponding models will be empty.
		 */
		virtual bool supportsCharges() const noexcept = 0;

		/**
		 * Reads the surface model and charges from the given file.
		 *
		 * @param filename path to an HMO file
		 * @throws FileAccessError if the given file is not readable
		 * @throws FileFormatError if the given HMO file is corrupt or unsupported
		 */
		virtual SurfaceModel readSurfaceModel(const std::string& filename) = 0;
	};

}

#endif // ANYBEM_READER_H
