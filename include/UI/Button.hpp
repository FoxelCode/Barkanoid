#pragma once

#include <functional>
#include <SFML/Graphics/Text.hpp>

#include "UI/UIObject.hpp"
#include "UI/Alignment.hpp"

typedef std::function<void()> ButtonCallback;
typedef std::function<void(std::string)> ButtonStringCallback;

class Button : public UIObject
{
public:
	enum State
	{
		Neutral,
		Hovered,
		Pressed
	};

	Button(sf::Vector2f pos, sf::Vector2f size, ButtonCallback callback, Alignment align = Alignment());
	Button(sf::Vector2f pos, sf::Vector2f size, ButtonStringCallback callback, Alignment align = Alignment());
	~Button() {}
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void LoadButtonGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border);
	void CenterText();

	void SetActive(bool active);

	State GetState() { return state; }
	sf::Text* GetText() { return &text; }

private:
	void SetState(State state);

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

	bool active;

	CallbackType callbackType;
	Callback callback;
	State state;
	bool pressed;

	sf::Text text;
};