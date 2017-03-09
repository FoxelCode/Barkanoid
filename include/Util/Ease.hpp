#pragma once

class Ease
{
public:
	enum Type
	{
		Linear,
		QuadOut,
		QuartOut
	};

	static inline float LinearTween(float time, float start, float change, float duration)
	{
		return change * time / duration + start;
	}
	static inline float QuadOutTween(float time, float start, float change, float duration)
	{
		time /= duration;
		return -change * time * (time - 2.0f) + start;
	}
	static inline float QuartOutTween(float time, float start, float change, float duration)
	{
		time /= duration;
		time--;
		return -change * (time * time * time * time - 1) + start;
	}
};