#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "UI/UIObject.hpp"

class TextField : public UIObject
{
public:
	enum State
	{
		OutOfFocus,
		Focused
	};

	TextField(sf::Vector2f pos, sf::Vector2f size, Alignment align = Alignment());
	~TextField() {}
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void LoadTextFieldGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border);
	void CenterText();

	sf::Text* GetText() { return &text; }

private:
	void SetState(State state);
	void TextEntered(std::string str);

	State state;
	sf::Text text;

	sf::RectangleShape cursor;
	const float cursorBlinkTime;
	float cursorBlinkTimer;
	bool cursorVisible;
};