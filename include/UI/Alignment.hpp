#pragma once

enum HorizontalAlign
{
	Left,
	Middle,
	Right
};

enum VerticalAlign
{
	Top,
	Center,
	Bottom
};

struct Alignment
{
	Alignment() : horizontal(HorizontalAlign::Left), vertical(VerticalAlign::Top) {}
	Alignment(HorizontalAlign horizontal, VerticalAlign vertical) : horizontal(horizontal), vertical(vertical) {}

	HorizontalAlign horizontal;
	VerticalAlign vertical;
};