#pragma once

#include <vector>

namespace NUtils {
	template<typename T>
		T FromString(const std::string&& s);

	template<>
		int FromString(const std::string&& s) {
			return std::stoi(s);
		}

	template<>
		std::string FromString(const std::string&& s) {
			return s;
		}

	template<typename T>
		std::vector<T> SplitBy(const std::string& s, char c) {
			auto l = 0;
			auto r = s.find(c);
			std::vector<T> result;

			while (r != std::string::npos) {
				result.push_back(FromString<T>(s.substr(l, r - l)));
				l = r + 1;
				r = s.find(c, l);
			}

			result.push_back(FromString<T>(s.substr(l)));
			return result;
		}
	
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
}
