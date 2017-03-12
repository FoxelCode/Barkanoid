#pragma once

#include "Graphic.hpp"

class SlicedGraphic : public Graphic
{
public:
	SlicedGraphic(Alignment align = Alignment::TopLeft);

	void SetBorder(sf::Vector2f border);

private:
	virtual void UpdateVertices();

	sf::Vector2f border;
};