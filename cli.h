#pragma once

#include <set>
#include <unordered_map>
#include <string>
#include <iostream>

namespace NCli {

class TArguments {
public:
	TArguments(int argc, char **argv);
	

	bool HasFlag(const std::string& flag) const;
	bool HasParameter(const std::string& parameter) const;
	const std::string& GetParameter(const std::string& parameter) const;

private:
	std::set<std::string> Flags;
	std::unordered_map<std::string, std::string> Parameters;
};

} // namespace NCli
