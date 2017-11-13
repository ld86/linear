#pragma once

#include <set>
#include <unordered_map>
#include <string>
#include <iostream>

namespace NCli {
	class TArguments {
	public:
		TArguments(int argc, char **argv);
		
	private:
		std::set<std::string> Flags;
		std::unordered_map<std::string, std::string> Parameters;
	};
};
