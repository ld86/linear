#include <utils.h>

#include <string>

namespace NUtils {

bool StartsWith(const std::string& s, const std::string& prefix) {
	if (prefix.length() > s.length()) {
		return false;
	}

	for (size_t i = 0; i < prefix.length(); ++i) {
		if (s[i] != prefix[i]) {
			return false;
		}
	}

	return true;
}

bool Contains(const std::string& s, const std::string& what) {
	return s.find(what) != std::string::npos;
}

template<>
	int FromString(const std::string&& s) {
		return std::stoi(s);
	}

template<>
	float FromString(const std::string&& s) {
		return std::stof(s);
	}

template<>
	std::string FromString(const std::string&& s) {
		return s;
	}

} // namespace NUtils
