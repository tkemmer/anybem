#ifndef ANYBEM_ERROR_H
#define ANYBEM_ERROR_H

#include <stdexcept>
#include <string>

namespace anybem {

	class IOError : public std::runtime_error {
	public:
		explicit IOError(const std::string& what) :
			std::runtime_error{what} {
		}
	};

	class FileAccessError : public IOError {
	public:
		explicit FileAccessError(const std::string& what) :
			IOError(what) {
		}
	};

	class FileFormatError : public IOError {
	public:
		explicit FileFormatError(const std::string& what) :
			IOError(what) {
		}
	};

}

#endif // ANYBEM_ERROR_H
