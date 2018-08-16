#include "hmo_reader.h"
#include "error.h"
#include "util.h"

using namespace std;
using namespace std::string_literals;

namespace anybem {

	// ================================================================================================================
	class HMOReaderImpl {
	public:
		std::vector<Node>     nodes    {0};
		std::vector<Triangle> elements {0};
		std::vector<Charge>   charges  {0};

		HMOReaderImpl(const string& filename) {
			ifstream fin(filename);
			if(fin.rdstate() & ifstream::failbit)
				throw FileAccessError("Cannot open file "s + filename);

			read_nodes(fin);
			read_elements(fin);
			read_charges(fin);
		}

		~HMOReaderImpl() = default;

		/// Clears the current surface model and charges
		void clear() noexcept {
			nodes.clear();
			elements.clear();
			charges.clear();
		}

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
			next_line(fin); // we're only interested in the first number

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
					throw FileFormatError{"Corrupt HMO file: missing element no. "s + to_string(i)};
				}

				auto v1 = 0, v2 = 0, v3 = 0;
				fin >> v1 >> v2 >> v3;
				elements.push_back({v1 - 1, v2 - 1, v3 - 1, 0, 0, 0, 0});
			}

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

			if(!next_line_matches(fin, "END_CHARGE_DATA"s)) {
				clear();
				throw FileFormatError{"Corrupt HMO file: missing END_CHARGE_DATA after node no. "s + to_string(maxn)};
			}
		}

	};


	// ================================================================================================================
	SurfaceModel HMOReader::readSurfaceModel(const std::string& filename) {
		HMOReaderImpl reader(filename);
		return {
			NodeBuffer{move(reader.nodes)},
			SurfaceElementBuffer{move(reader.elements)},
			ChargeBuffer{move(reader.charges)}
		};
	}

}