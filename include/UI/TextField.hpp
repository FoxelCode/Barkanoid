#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Engine/GameObject.hpp"

class TextField : public GameObject
{
public:
	enum State
	{
		OutOfFocus,
		Focused
	};

	TextField(sf::Vector2f pos, sf::Vector2f size);
	~TextField() {}
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text* GetText() { return &text; }

private:
	State state;

	sf::Vector2f size;
	sf::Text text;
};