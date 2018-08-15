#include "hmo_reader.h"
#include "impala.h"

#include <clipp.h>

#include <iostream>

using namespace clipp;
using namespace anybem;
using namespace std;
using namespace std::string_literals;

int main(int argc, char** argv) {
	auto hmo_file = ""s;

	group cli{
		value("hmo file"s, hmo_file) % "Input file with a triangulated surface model and charges"s
	};

	if(!parse(argc, argv, cli)) {
		cout << make_man_page(cli, argv[0])
			.prepend_section("NAME"s, "AnyBEM - Nonlocal Protein Electrostatics in Impala"s);
		return 1;
	}

	HMOReader reader(hmo_file);
	cout << "HMO file statistics:\n"s
	     << " * Nodes:    "s << to_string(reader.nodes().size()) << "\n"s
	     << " * Elements: "s << to_string(reader.elements().size()) << "\n"s
	     << " * Charges:  "s << to_string(reader.charges().size()) << "\n"s;

	cout << "\n";
	anybem_node_buffer_stats(reader.nodes().data(), reader.nodes().size());

	cout << "\n";
	anybem_surface_element_buffer_stats(reader.elements().data(), reader.elements().size());

	cout << "\n";
	anybem_charge_buffer_stats(reader.charges().data(), reader.charges().size());
}
