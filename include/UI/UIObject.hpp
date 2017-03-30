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

	virtual void SetSize(sf::Vector2f size);

	sf::Vector2f GetOffset() const;
	sf::Vector2f GetSize() { return size; }

protected:
	void UpdateSize();

	Alignment align;
	sf::Vector2f size;
};