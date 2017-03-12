#include "Util/Tween.hpp"

std::vector<Tween::TweenInstance*> Tween::tweens;

void Tween::Start(Ease::Type easeType, float start, float end, float duration, TweenUpdate update, TweenComplete complete, Tween::Type tweenType, float delay)
{
	TweenInstance* tween = new TweenInstance(easeType, start, end, duration, update, complete, tweenType, delay);
	tweens.push_back(tween);
}

void Tween::Run(TweenInstance* tween)
{
	tween->persist = true;
	tweens.push_back(tween);
}

void Tween::UpdateTweens(float delta)
{
	for (auto it = tweens.begin(); it != tweens.end(); )
	{
		UpdateTween(*(*it), delta);
		if (!(*it)->persist && (*it)->done)
		{
			TweenInstance* toDelete = (*it);
			it = tweens.erase(it);
			delete toDelete;
			toDelete = nullptr;
		}
		else
			it++;
	}
}

void Tween::StopAll()
{
	for (auto it = tweens.begin(); it != tweens.end(); )
	{
		TweenInstance* toDelete = (*it);
		it = tweens.erase(it);
		delete toDelete;
		toDelete = nullptr;
	}
	tweens.clear();
}

void Tween::RemoveTween(TweenInstance* tween)
{
	for (auto it = tweens.begin(); it != tweens.end(); it++)
	{
		if ((*it) == tween)
		{
			tweens.erase(it);
			return;
		}
	}
}

void Tween::UpdateTween(TweenInstance& tween, float delta)
{
	if (!tween.done)
	{
		tween.time += delta;
		//tween.time = Math::clamp(tween.time, 0.0f, tween.delay + tween.duration);

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
			if (tween.update != nullptr)
				tween.update(value);
		}

		if (tween.time >= (tween.duration + tween.delay))
		{
			switch (tween.tweenType)
			{
			case Type::OneShot:
				tween.update(tween.start + tween.change);
				break;
			case Type::Boomerang:
				tween.update(tween.start);
				break;
			}
			if (tween.complete != nullptr)
				tween.complete();
			tween.done = true;
		}
	}
}