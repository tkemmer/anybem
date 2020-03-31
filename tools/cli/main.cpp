#include <anybem/hmo_reader.h>
#include <anybem/impala.h>

#include <clipp.h>

#include <iostream>

using namespace clipp;
using namespace anybem;
using namespace std;
using namespace std::string_literals;

int main(int argc, char** argv) {
	auto hmo_file = ""s;
	auto params   = default_params;

	auto cli = (
		"Input file with a triangulated surface model and charges"s %
			value("hmo file"s, hmo_file),
		("Dielectric constant of the solute (default: "s + to_string(params.epsOmega) + ")"s) %
			option("--eps-omega"s) & value("val"s, params.epsOmega),
		("Dielectric constant of the solvent (default: "s + to_string(params.epsSigma) + ")"s) %
			option("--eps-sigma"s) & value("val"s, params.epsSigma),
		("Large-scale solvent response (default: "s + to_string(params.epsInf) + ")"s) %
			option("--eps-inf"s) & value("val"s, params.epsInf),
		("Correlation length scale (in Angstrom; default: "s + to_string(params.lambda) + ")"s) %
			option("--lambda"s) & value("val"s, params.lambda)
	);

	if(!parse(argc, argv, cli)) {
		cout << make_man_page(cli, argv[0])
			.prepend_section("NAME"s, "AnyBEM - Nonlocal Protein Electrostatics in Impala"s);
		return 1;
	}

	HMOReader reader;
	auto surf = reader.readSurfaceModel(hmo_file);
	surf.params(params);

	cout << "HMO file statistics:\n"s
	     << " * Elements: "s << to_string(surf.element_count()) << "\n"s
	     << " * Charges:  "s << to_string(surf.charge_count()) << "\n"s
	     << "\n"s;

	auto sproto = surf.prototype();
	anybem_surface_model_stats(&sproto);
}
