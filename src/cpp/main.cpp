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

	HMOReader reader;
	auto sh = reader.readSurfaceModel(hmo_file);

	cout << "HMO file statistics:\n"s
	     << " * Nodes:    "s << to_string(sh.node_count()) << "\n"s
	     << " * Elements: "s << to_string(sh.element_count()) << "\n"s
	     << " * Charges:  "s << to_string(sh.charge_count()) << "\n"s
	     << "\n"s;

	auto surf = sh.get();
	anybem_surface_model_stats(&surf);
}
