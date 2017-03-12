#include "UI/Button.hpp"

#include "Graphics/SlicedGraphic.hpp"
#include "Engine/Input.hpp"
#include "Util/Math.hpp"
#include "Collision/AABBCollider.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f size, ButtonCallback callback, Alignment align)
	: UIObject(pos, size, align), callbackType(CallbackType::Void), callback(callback), state(State::Neutral), pressed(false)
{
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, ButtonStringCallback callback, Alignment align)
	: UIObject(pos, size, align), callbackType(CallbackType::String), callback(callback), state(State::Neutral), pressed(false)
{
}

void Button::Update(float delta)
{
	if (active)
	{
		bool hovering = Math::contains(sf::Vector2f(Input::GetMousePosition()), collider->GetBounds());

		if (hovering && Input::MouseJustPressed(sf::Mouse::Left))
		{
			pressed = true;
		}

		if (Input::MouseJustReleased(sf::Mouse::Left))
		{
			if (hovering && pressed)
			{
				switch (callbackType)
				{
				case Button::Void:
					callback.callback();
					break;
				case Button::String:
					callback.stringCallback(text.getString());
					break;
				}
			}
			pressed = false;
		}

		if (hovering)
		{
			if (pressed)
				SetState(State::Pressed);
			else
				SetState(State::Hovered);
		}
		else
			SetState(State::Neutral);
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
	states.transform.translate(GetPosition());
	target.draw(text, states);
}

void Button::LoadButtonGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border)
{
	LoadSlicedGraphic(tex);
	graphic->SetFrameSize(frameSize);
	graphic->SetSize(size);
	static_cast<SlicedGraphic*>(graphic)->SetBorder(border);
}

void Button::CenterText()
{
	sf::Vector2f textPos = sf::Vector2f(size.x / 2.0f - text.getGlobalBounds().width / 2.0f, 0.0f) + GetOffset();
	text.setPosition(textPos);
}

void Button::SetActive(bool active)
{
	this->active = active;
	if (!active)
		SetState(State::Neutral);
}

void Button::SetState(State state)
{
	this->state = state;
	if (graphic != nullptr)
		graphic->SetFrame((int)state);
}
