#pragma once

#include <vector>
#include <tuple>

#include "Util/Random.hpp"

template <class T>
class WeightedVector
{
public:
	WeightedVector() {}
	~WeightedVector() { members.clear(); }

	void Add(T data, float weight);
	T GetRandom();

private:
	struct WeightedMember
	{
		T data;
		float weight;
		float cumulative;
	};

	std::vector<WeightedMember> members;
};

template<class T>
inline void WeightedVector<T>::Add(T data, float weight)
{
	WeightedMember newMember;
	newMember.data = data;
	newMember.weight = weight;
	if (members.empty())
		newMember.cumulative = weight;
	else
		newMember.cumulative = members.back().cumulative + weight;
	members.push_back(newMember);
}

template<class T>
inline T WeightedVector<T>::GetRandom()
{
	if (members.size() == 0)
		return T();
	if (members.size() == 1)
		return members[0].data;

	float pick = Random::Float(members.back().cumulative);
	for (WeightedMember& member : members)
	{
		if (member.cumulative > pick)
			return member.data;
	}
	LOG_ERROR("Couldn't get random member, this probably shouldn't happen");
	return T();
}
