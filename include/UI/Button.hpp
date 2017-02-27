#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Engine/GameObject.hpp"

typedef void(*ButtonCallback)();

enum ButtonState
{
	Neutral,
	Hovered,
	Pressed
};

class Button : public GameObject
{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, ButtonCallback callback);
	~Button();
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void LoadButtonGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border);
	void CenterText();

	void SetCallback(ButtonCallback callback) { this->callback = callback; }

	ButtonState GetState() { return state; }
	sf::Text* GetText() { return &text; }

protected:
	void SetState(ButtonState state);

private:
	ButtonCallback callback = nullptr;
	ButtonState state = ButtonState::Neutral;
	bool pressed = false;

	sf::Vector2f size;
	sf::Text text;
};