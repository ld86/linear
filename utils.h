#pragma once

#include <string>
#include <vector>

namespace NUtils {

template<typename T>
T FromString(const std::string&& s);

template<> 
int FromString(const std::string&& s);

template<>
float FromString(const std::string&& s);

template<>
std::string FromString(const std::string&& s);

template<typename T>
	std::vector<T> SplitBy(const std::string& s, const std::string& sep) {
		auto l = 0;
		auto r = s.find(sep);
		std::vector<T> result;

		while (r != std::string::npos) {
			result.push_back(FromString<T>(s.substr(l, r - l)));
			l = r + sep.length();
			r = s.find(sep, l);
		}

		result.push_back(FromString<T>(s.substr(l)));
		return result;
	}

bool StartsWith(const std::string& s, const std::string& prefix);
bool Contains(const std::string& s, const std::string& what);


} // namespace NUtils
