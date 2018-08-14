#ifndef ANYBEM_HMO_READER_H
#define ANYBEM_HMO_READER_H

#include "model.h"

#include <memory>
#include <string>
#include <vector>

namespace anybem {

	/**
	 * HMO file reader for triangulated surfaces (and charges).
	 *
	 * This file format is somewhat ancient and the only source for the format specification - to the best of my
	 * knowledge - is https://espace.cern.ch/roxie/Documentation/ironFileDoc.pdf. However, we seem to use a modified
	 * version of the original format with an additional section for charges:
	 *
	 * <pre>
	 * BEGIN_NODL_DATA
	 *    <number of nodes>
	 *    1   <x>   <y>   <z>
	 *    2   <x>   <y>   <z>
	 *    ...
	 * END_NODL_DATA
	 *
	 * BEGIN_ELEM_DATA
	 *    <number of elements> <unused>...
	 *    1   1   103   <index node1>   <index node2>   <index node3>
	 *    2   1   103   <index node1>   <index node2>   <index node3>
	 *    ...
	 * END_ELEM_DATA
	 *
	 * BEGIN_CHARGE_DATA
	 *    <number of charges>
	 *    1   <x>   <y>   <z>   <charge>
	 *    2   <x>   <y>   <z>   <charge>
	 *    ...
	 * END_CHARGE_DATA
	 * </pre>
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
