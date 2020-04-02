#ifndef ANYBEM_TYPES_H
#define ANYBEM_TYPES_H

#include <cstdlib>

namespace anybem {
	using real_t     = double;
	using index_t    = int32_t;

	struct Position {
		real_t x;
		real_t y;
		real_t z;
	};
}

#endif // ANYBEM_TYPES_H
