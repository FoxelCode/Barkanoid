#pragma once

#include <functional>
#include <SFML/Graphics/Text.hpp>

#include "Engine/GameObject.hpp"

typedef std::function<void()> ButtonCallback;
typedef std::function<void(std::string)> ButtonStringCallback;

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
	Button(sf::Vector2f pos, sf::Vector2f size, ButtonStringCallback callback);
	~Button();
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void LoadButtonGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border);
	void CenterText();

	ButtonState GetState() { return state; }
	sf::Text* GetText() { return &text; }

protected:
	void SetState(ButtonState state);

private:
	enum CallbackType
	{
		Void,
		String
	};
	union Callback
	{
		ButtonCallback callback;
		ButtonStringCallback stringCallback;
		Callback(ButtonCallback callback) : callback(callback) {}
		Callback(ButtonStringCallback stringCallback) : stringCallback(stringCallback) {}
		~Callback() {}
	};

	CallbackType callbackType;
	Callback callback;
	ButtonState state = ButtonState::Neutral;
	bool pressed = false;

	sf::Vector2f size;
	sf::Text text;
};