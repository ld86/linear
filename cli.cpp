#include <cli.h>

namespace NCli {
	TArguments::TArguments(int argc, char **argv) {
		for (size_t i = 1; i < argc; ++i) {
			std::cout << argv[i] << std::endl;
		}
	}
}
