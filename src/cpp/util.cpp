#include <anybem/util.h>

using namespace std;

namespace anybem {

	void next_line(ifstream &fin) {
		if (!fin.good())
			return;
		string line;
		getline(fin, line);
	}

	bool next_line_matches(ifstream &fin, const string &query) {
		next_line(fin);
		if (!fin.good())
			return false;
		string line;
		return getline(fin, line) && line == query;
	}

	void seek_line(ifstream &fin, const string &query) {
		if (!fin.good())
			return;
		for (string line; getline(fin, line);)
			if (line == query)
				break;
	}

}
