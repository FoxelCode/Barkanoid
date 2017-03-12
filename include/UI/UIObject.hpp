#pragma once

#include "Engine/GameObject.hpp"
#include "UI/Alignment.hpp"

class UIObject : public GameObject
{
public:
	UIObject(sf::Vector2f pos, sf::Vector2f size, Alignment align);
	virtual ~UIObject() {}

	void LoadGraphic(sf::Texture* tex);
	void LoadSlicedGraphic(sf::Texture* tex);

protected:
	sf::Vector2f GetOffset();

	Alignment align;
	sf::Vector2f size;
};