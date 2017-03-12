#include "Util/Tween.hpp"

std::vector<Tween::TweenInstance> Tween::tweens;

void Tween::Start(Ease::Type easeType, float start, float end, float duration, TweenUpdate update, TweenComplete complete, Tween::Type tweenType, float delay)
{
	TweenInstance tween(easeType, start, end, duration, update, complete, tweenType, delay);
	tweens.push_back(tween);
}

void Tween::UpdateTweens(float delta)
{
	for (auto it = tweens.begin(); it != tweens.end(); )
	{
		UpdateTween((*it), delta);
		if ((*it).done)
			it = tweens.erase(it);
		else
			it++;
	}
}

void Tween::StopAll()
{
	tweens.clear();
}

void Tween::UpdateTween(TweenInstance& tween, float delta)
{
	tween.time += delta;

	if (tween.time >= tween.delay)
	{
		float value;
		switch (tween.tweenType)
		{
		case Type::OneShot:
			value = Ease::easeFunctions[tween.easeType](tween.time - tween.delay, tween.start, tween.change, tween.duration);
			break;

		case Type::Boomerang:
			if (tween.time - tween.delay <= tween.duration / 2.0f)
				value = Ease::easeFunctions[tween.easeType](tween.time - tween.delay, tween.start, tween.change, tween.duration / 2.0f);
			else
				value = Ease::easeFunctions[tween.easeType](tween.duration / 2.0f - ((tween.time - tween.duration / 2.0f) - tween.delay), tween.start, tween.change, tween.duration / 2.0f);
			break;
		}
		tween.update(value);
	}

	if (tween.time >= (tween.duration + tween.delay))
	{
		if (tween.complete != nullptr)
			tween.complete();
		tween.done = true;
	}
}