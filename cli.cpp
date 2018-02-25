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
			if (NUtils::Contains(argument, sep)) {
				auto parts = NUtils::SplitBy<std::string>(argument, sep);
				if (parts.size() != 2) {
					throw std::logic_error("Found separator in key value");
				}
				Parameters.insert({parts[0], parts[1]});
			} else {
				Flags.insert(argument);
			}
		}
	}
}

bool TArguments::HasFlag(const std::string& flag) const {
	return Flags.find(flag) != Flags.end();
}

bool TArguments::HasParameter(const std::string& parameter) const {
	return Parameters.find(parameter) != Parameters.end();
}

const std::string& TArguments::GetParameter(const std::string& parameter) const {
	return Parameters.at(parameter);
}

} // namespace NCli
