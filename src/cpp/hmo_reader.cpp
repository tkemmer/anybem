#include <anybem/hmo_reader.h>

#include <anybem/error.h>
#include <anybem/util.h>

using namespace std;
using namespace std::string_literals;

namespace anybem {

	// ================================================================================================================
	class HMOReaderImpl {
	public:
		std::vector<NodePrimitive>     nodes    {0};
		std::vector<TrianglePrimitive> elements {0};
		std::vector<ChargePrimitive>   charges  {0};

		explicit HMOReaderImpl(const string& filename) {
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
			index_t num_nodes = 0;
			fin >> num_nodes;
			if(num_nodes < 0) {
				clear();
				throw FileFormatError{
					"Corrupt HMO file: number of nodes out of range ("s + to_string(num_nodes) + ")"s
				};
			}
			nodes.reserve(static_cast<unsigned long>(num_nodes));

			for(index_t i = 0; i < num_nodes; ++i) {
				if(!fin.good()) {
					clear();
					throw FileFormatError{"Corrupt HMO file: missing node no. "s + to_string(i)};
				}

				index_t idx = 0;
				fin >> idx;

				if(idx != i + 1)
				{
					clear();
					throw FileFormatError{"Corrupt HMO file: missing node no. "s + to_string(i)};
				}

				real_t x = 0, y = 0, z = 0;
				fin >> x >> y >> z;
				nodes.push_back({x, y, z});
			}

			if(!next_line_matches(fin, "END_NODL_DATA"s)) {
				clear();
				throw FileFormatError{"Corrupt HMO file: missing END_NODL_DATA after node no. "s + to_string(num_nodes)};
			}
		}

		void read_elements(ifstream& fin) {
			seek_line(fin, "BEG_ELEM_DATA"s);
			index_t num_elem = 0;
			fin >> num_elem;
			if(num_elem < 0) {
				clear();
				throw FileFormatError{
					"Corrupt HMO file: number of elements out of range ("s + to_string(num_elem) + ")"s
				};
			}
			elements.reserve(static_cast<unsigned long>(num_elem));
			next_line(fin); // we're only interested in the first number

			for(index_t i = 0; i < num_elem; ++i) {
				if(!fin.good()) {
					clear();
					throw FileFormatError{"Corrupt HMO file: missing element no. "s + to_string(i)};
				}

				index_t idx = 0;
				auto components = 0, configuration = 0;
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

				index_t v1 = 0, v2 = 0, v3 = 0;
				fin >> v1 >> v2 >> v3;
				auto num_nodes = static_cast<index_t>(nodes.size());
				if(v1 < 1 || v1 > num_nodes) {
					clear();
					throw FileFormatError{
						"Corrupt HMO file: invalid v1 index "s + to_string(v1) + " in element no. "s + to_string(i)
					};
				}
				if(v2 < 1 || v2 > num_nodes) {
					clear();
					throw FileFormatError{
						"Corrupt HMO file: invalid v2 index "s + to_string(v2) + " in element no. "s + to_string(i)
					};
				}
				if(v3 < 1 || v3 > num_nodes) {
					clear();
					throw FileFormatError{
						"Corrupt HMO file: invalid v3 index "s + to_string(v3) + " in element no. "s + to_string(i)
					};
				}
				elements.push_back({--v1, --v2, --v3});
			}

			if(!next_line_matches(fin, "END_ELEM_DATA"s)) {
				clear();
				throw FileFormatError{
					"Corrupt HMO file: missing END_ELEM_DATA after node no. "s + to_string(num_elem)
				};
			}
		}

		void read_charges(ifstream& fin) {
			seek_line(fin, "BEG_CHARGE_DATA"s);
			index_t num_charges = 0;
			fin >> num_charges;
			if(num_charges < 0) {
				clear();
				throw FileFormatError{
					"Corrupt HMO file: number of charges out of range ("s + to_string(num_charges) + ")"s
				};
			}
			charges.reserve(static_cast<unsigned long>(num_charges));

			for(index_t i = 0; i < num_charges; ++i) {
				if(!fin.good()) {
					clear();
					throw FileFormatError{"Corrupt HMO file: missing charge no. "s + to_string(i)};
				}

				index_t idx = 0;
				fin >> idx;

				if(idx != i + 1)
				{
					clear();
					throw FileFormatError{"Corrupt HMO file: missing charge no. "s + to_string(i)};
				}

				real_t x = 0, y = 0, z = 0, q = 0;
				fin >> x >> y >> z >> q;
				charges.push_back({{x, y, z}, q});
			}

			if(!next_line_matches(fin, "END_CHARGE_DATA"s)) {
				clear();
				throw FileFormatError{
					"Corrupt HMO file: missing END_CHARGE_DATA after node no. "s + to_string(num_charges)
				};
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