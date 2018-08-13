#include "hmo_reader.h"
#include "error.h"

#include <fstream>

using namespace std;
using namespace std::string_literals;

namespace anybem {

	// ================================================================================================================
	class HMOReader::Impl{
	public:
		std::vector<position_t> nodes   ;
		std::vector<Triangle>   elements;
		std::vector<Charge>     charges ;

		Impl(const string& filename) {
			ifstream fin(filename);
			if(fin.rdstate() & ifstream::failbit)
				throw FileAccessError("Cannot open file "s + filename);

			read_nodes(fin);
			read_elements(fin);
			read_charges(fin);
		}

		~Impl() = default;

	private:
		void read_nodes(ifstream& fin) {
			seek_line(fin, "BEG_NODL_DATA"s);
			auto maxn = 0ul;
			fin >> maxn;
			nodes.reserve(maxn);

			for(auto i = 0u; i < maxn; ++i) {
				if(!fin.good()) {
					clear();
					throw FileFormatError{"Corrupt HMO file: missing node no. "s + to_string(i)};
				}

				auto idx = 0;
				fin >> idx;

				if(idx != i + 1)
				{
					clear();
					throw FileFormatError{"Corrupt HMO file: missing node no. "s + to_string(i)};
				}

				auto x = 0., y = 0., z = 0.;
				fin >> x >> y >> z;
				nodes.push_back({x, y, z});
			}

			skip_line(fin); // skip the newline of the last node line
			if(!next_line_matches(fin, "END_NODL_DATA"s)) {
				clear();
				throw FileFormatError{"Corrupt HMO file: missing END_NODL_DATA after node no. "s + to_string(maxn)};
			}
		}

		void read_elements(ifstream& fin) {
			seek_line(fin, "BEG_ELEM_DATA"s);
			auto maxn = 0ul;
			fin >> maxn;
			elements.reserve(maxn);
			skip_line(fin); // we're only interested in the first number

			for(auto i = 0u; i < maxn; ++i) {
				if(!fin.good()) {
					clear();
					throw FileFormatError{"Corrupt HMO file: missing element no. "s + to_string(i)};
				}

				auto idx = 0, components = 0, configuration = 0;
				fin >> idx >> components >> configuration;

				if(components != 1) {
					clear();
					throw FileFormatError{"Unsupported HMO file: multi-component elements are not supported"s};
				}

				if(configuration != 103) {
					clear();
					throw FileFormatError{"Unsupported HMO file: elements must be triangles (configuration: 103)"s};
				}

				if(idx != i + 1)
				{
					clear();
					throw FileFormatError{"Corrupt HMO file: missing node no. "s + to_string(i)};
				}

				auto v1 = 0, v2 = 0, v3 = 0;
				fin >> v1 >> v2 >> v3;
				elements.push_back({v1, v2, v3, 0, 0, 0, 0});
			}

			skip_line(fin); // skip the newline of the last element line
			if(!next_line_matches(fin, "END_ELEM_DATA"s)) {
				clear();
				throw FileFormatError{"Corrupt HMO file: missing END_ELEM_DATA after node no. "s + to_string(maxn)};
			}
		}

		void read_charges(ifstream& fin) {
			seek_line(fin, "BEG_CHARGE_DATA"s);
			auto maxn = 0ul;
			fin >> maxn;
			charges.reserve(maxn);

			for(auto i = 0u; i < maxn; ++i) {
				if(!fin.good()) {
					clear();
					throw FileFormatError{"Corrupt HMO file: missing charge no. "s + to_string(i)};
				}

				auto idx = 0;
				fin >> idx;

				if(idx != i + 1)
				{
					clear();
					throw FileFormatError{"Corrupt HMO file: missing charge no. "s + to_string(i)};
				}

				auto x = 0., y = 0., z = 0., q = 0.;
				fin >> x >> y >> z >> q;
				charges.push_back({{x, y, z}, q});
			}

			skip_line(fin); // skip the newline of the last charge line
			if(!next_line_matches(fin, "END_CHARGE_DATA"s)) {
				clear();
				throw FileFormatError{"Corrupt HMO file: missing END_CHARGE_DATA after node no. "s + to_string(maxn)};
			}
		}

		void seek_line(ifstream& fin, const string& query) {
			if(!fin.good())
				return;
			for(string line; getline(fin, line);)
				if(line == query)
					break;
		}

		void skip_line(ifstream& fin) {
			if(!fin.good())
				return;
			string line;
			getline(fin, line);
		}

		bool next_line_matches(ifstream& fin, const string& query) {
			if(!fin.good())
				return false;
			string line;
			return getline(fin, line) && line == query;
		}

		void clear() {
			nodes.clear();
			elements.clear();
			charges.clear();
		}
	};


	// ================================================================================================================
	HMOReader::HMOReader(const string& filename) :
		impl_{make_unique<HMOReader::Impl>(filename)} {
	}

	HMOReader::~HMOReader() noexcept = default;

	vector<position_t>& HMOReader::getNodes() noexcept { return impl_->nodes; }

	vector<Triangle>& HMOReader::getElements() noexcept { return impl_->elements; }

	vector<Charge>& HMOReader::getCharges() noexcept { return impl_->charges; }

}