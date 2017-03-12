#pragma once

#include <functional>
#include <vector>

#include "Ease.hpp"

class Tween
{
public:
	typedef std::function<void(float)> TweenUpdate;
	typedef std::function<void()> TweenComplete;

	enum Type
	{
		OneShot,
		Boomerang
	};

	struct TweenInstance
	{
		TweenInstance(Ease::Type type, float start, float end, float duration,TweenUpdate update,
			TweenComplete complete = nullptr, Type tweenType = Type::OneShot, float delay = 0.0f)
			: easeType(type), start(start), change(end - start), time(0.0f), delay(delay),
			duration(duration), done(false), update(update), complete(complete), tweenType(tweenType), persist(false) {}

		void Reset()
		{
			time = 0.0f;
			done = false;
		}
		void Finish()
		{
			time = duration;
			done = true;
		}

		Ease::Type easeType;
		Type tweenType;
		float start;
		float change;
		float time;
		float delay;
		float duration;
		bool done;
		TweenUpdate update;
		TweenComplete complete;
		bool persist;
	};

	static void Start(Ease::Type type, float start, float end, float duration, TweenUpdate update,
		TweenComplete complete = nullptr, Type tweenType = Type::OneShot, float delay = 0.0f);
	static void Run(TweenInstance* tween);
	static void UpdateTweens(float delta);
	static void StopAll();
	static void RemoveTween(TweenInstance* tween);

private:
	static void UpdateTween(TweenInstance& tween, float delta);

	static std::vector<TweenInstance*> tweens;
};