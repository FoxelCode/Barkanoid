#include "Util/Ease.hpp"

std::map<Ease::Type, Ease::EaseFunction> Ease::easeFunctions = {
	{ Ease::Type::Linear, &Ease::LinearTween },
	{ Ease::Type::QuadIn, &Ease::QuadInTween },
	{ Ease::Type::QuadOut, &Ease::QuadOutTween },
	{ Ease::Type::QuadInOut, &Ease::QuadInOutTween },
	{ Ease::Type::CubicIn, &Ease::CubicInTween },
	{ Ease::Type::CubicOut, &Ease::CubicOutTween },
	{ Ease::Type::CubicInOut, &Ease::CubicInOutTween },
	{ Ease::Type::QuartIn, &Ease::QuartInTween },
	{ Ease::Type::QuartOut, &Ease::QuartOutTween },
	{ Ease::Type::QuartInOut, &Ease::QuartInOutTween }
};