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
		switch (tween.easeType)
		{
		case Ease::Type::Linear:
			value = Ease::LinearTween(tween.time - tween.delay, tween.start, tween.change, tween.duration);
			break;
		case Ease::Type::QuadOut:
			value = Ease::QuadOutTween(tween.time - tween.delay, tween.start, tween.change, tween.duration);
			break;
		case Ease::Type::QuartOut:
			value = Ease::QuartOutTween(tween.time - tween.delay, tween.start, tween.change, tween.duration);
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