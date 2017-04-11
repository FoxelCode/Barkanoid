#pragma once

#include <vector>
#include <SFML\System.hpp>

class Math
{
public:
	static sf::Vector2f normalise(sf::Vector2f a)
	{
		return a / magnitude(a);
	}

	static float magnitude(sf::Vector2f a)
	{
		return sqrtf(a.x * a.x + a.y * a.y);
	}

	static bool contains(sf::Vector2f a, sf::FloatRect b, bool includeEdges = true)
	{
		if (!includeEdges)
			return (a.x > b.left && a.x < b.left + b.width) && (a.y > b.top && a.y < b.top + b.height);
		return (a.x >= b.left && a.x <= b.left + b.width) && (a.y >= b.top && a.y <= b.top + b.height);
	}

	template <typename T>
	static T sign(T a)
	{
		if (a > 0) return 1;
		if (a < 0) return -1;
		return 0;
	}

	template <typename T>
	static void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template <typename T>
	static T min(T a, T b)
	{
		if (b < a) return b;
		return a;
	}

	template <typename T>
	static T max(T a, T b)
	{
		if (b > a) return b;
		return a;
	}

	template <typename T>
	static T clamp(T a, T mini, T maxi)
	{
		if (mini > maxi)
			swap(mini, maxi);
		return max(mini, min(a, maxi));
	}
};

const double PIELLO_DARKNESS_MY_OLD_FRIEND = 3.1415926535897;