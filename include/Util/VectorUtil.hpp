#pragma once

#include <vector>
#include <algorithm>

class VectorUtil
{
public:
	template <class T>
	static bool TryRemove(std::vector<T>& vec, const T& value);
};

template<class T>
inline bool VectorUtil::TryRemove(std::vector<T>& vec, const T& value)
{
	auto removeIt = std::find(vec.begin(), vec.end(), value);
	if (removeIt != vec.end())
	{
		vec.erase(removeIt);
		return true;
	}
	return false;
}
