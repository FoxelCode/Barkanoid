#include "UI/Button.hpp"

#include "Graphics/SlicedGraphic.hpp"
#include "Engine/Input.hpp"
#include "Util/Math.hpp"
#include "Collision/AABBCollider.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f size, ButtonCallback callback)
	: size(size), callback(callback)
{
	SetPosition(pos);

	collider = new AABBCollider(this, -size / 2.0f, size);
}

Button::~Button()
{
}

void Button::Update(float delta)
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
			callback();
		}
		pressed = false;
	}

	if (hovering)
	{
		if (pressed)
			SetState(ButtonState::Pressed);
		else
			SetState(ButtonState::Hovered);
	}
	else
		SetState(ButtonState::Neutral);
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
	graphic->setPosition(-size / 2.0f);
	static_cast<SlicedGraphic*>(graphic)->SetBorder(border);
}

void Button::CenterText()
{
	text.setPosition(-text.getGlobalBounds().width / 2.0f, -text.getGlobalBounds().height * 1.5f);
}

void Button::SetState(ButtonState state)
{
	this->state = state;
	if (graphic != nullptr)
		graphic->SetFrame((int)state);
}