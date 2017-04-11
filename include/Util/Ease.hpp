#pragma once

#include <map>

class Ease
{
public:
	typedef float(*EaseFunction)(float, float, float, float);

	enum Type
	{
		Linear,
		QuadIn,
		QuadOut,
		QuadInOut,
		CubicIn,
		CubicOut,
		CubicInOut,
		QuartIn,
		QuartOut,
		QuartInOut
	};

	static std::map<Type, EaseFunction> easeFunctions;

private:
	/*
	Easing functions by Robert Penner, from:
	http://gizma.com/easing/
	*/

	static float LinearTween(float time, float start, float change, float duration)
	{
		return change * time / duration + start;
	}
	static float QuadInTween(float time, float start, float change, float duration)
	{
		time /= duration;
		return change * time * time + start;
	}
	static float QuadOutTween(float time, float start, float change, float duration)
	{
		time /= duration;
		return -change * time * (time - 2.0f) + start;
	}
	static float QuadInOutTween(float time, float start, float change, float duration)
	{
		time /= duration / 2.0f;
		if (time < 1.0f) return change / 2.0f * time * time + start;
		time--;
		return -change / 2.0f * (time * (time - 2.0f) - 1.0f) + start;
	}
	static float CubicInTween(float time, float start, float change, float duration)
	{
		time /= duration;
		return change * time * time * time + start;
	}
	static float CubicOutTween(float time, float start, float change, float duration)
	{
		time /= duration;
		time--;
		return change * (time * time * time + 1.0f) + start;
	}
	static float CubicInOutTween(float time, float start, float change, float duration)
	{
		time /= duration / 2.0f;
		if (time < 1.0f) return change / 2.0f * time * time * time + start;
		time -= 2.0f;
		return change / 2.0f * (time * time * time + 2.0f) + start;
	}
	static float QuartInTween(float time, float start, float change, float duration)
	{
		time /= duration;
		return change * time * time * time * time + start;
	}
	static float QuartOutTween(float time, float start, float change, float duration)
	{
		time /= duration;
		time--;
		return -change * (time * time * time * time - 1) + start;
	}
	static float QuartInOutTween(float time, float start, float change, float duration)
	{
		time /= duration / 2.0f;
		if (time < 1.0f) return change / 2.0f * time * time * time * time + start;
		time -= 2.0f;
		return -change / 2.0f * (time * time * time * time - 2.0f) + start;
	}
};