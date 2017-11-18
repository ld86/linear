#include <cli.h>

#include <utils.h>

namespace NCli {
	TArguments::TArguments(int argc, char **argv) {
		const std::string prefix = "--";
		const std::string sep = "=";

		for (size_t i = 1; i < argc; ++i) {
			std::string argument{argv[i]};
			if (NUtils::StartsWith(argument, prefix)) {
				argument = argument.substr(prefix.length());
				std::cout << argument << std::endl;
			}
		}
	}
}
