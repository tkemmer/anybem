#ifndef ANYBEM_UTIL_H
#define ANYBEM_UTIL_H

#include <fstream>
#include <string>

namespace anybem {

	/// Fasts-forward behind the next newline character
	void next_line(std::ifstream &fin);

	/// Checks whether the next line matches the given query string
	bool next_line_matches(std::ifstream& fin, const std::string& query);

	/// Fasts-forward behind the query line (or to EOF if the query line is not found)
	void seek_line(std::ifstream& fin, const std::string& query);

}

#endif // ANYBEM_UTIL_H
