#ifndef ANYBEM_TYPES_H
#define ANYBEM_TYPES_H

#include <array>
#include <cstdlib>

namespace anybem {
	using real_t     = double;
	using index_t    = int64_t;
	using position_t = std::array<real_t, 3>;
}

#endif // ANYBEM_TYPES_H