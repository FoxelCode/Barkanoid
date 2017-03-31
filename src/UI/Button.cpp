#include "UI/Button.hpp"

#include "Graphics/SlicedGraphic.hpp"
#include "Engine/Input.hpp"
#include "Util/Math.hpp"
#include "Util/StringUtil.hpp"
#include "Collision/AABBCollider.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f size, ButtonCallback callback, Alignment align)
	: UIObject(pos, size, align), callbackType(CallbackType::Void), callback(callback),
		state(State::Neutral), pressed(false), textSpacing(10.0f, 10.0f), autoHeight(false)
{
	text = new MultilineText(textSpacing + GetOffset(), sf::Vector2f(size.x - textSpacing.x * 2.0f, size.y - textSpacing.y * 2.0f));
	text->SetTextAlignment(Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, ButtonStringCallback callback, Alignment align)
	: UIObject(pos, size, align), callbackType(CallbackType::String), callback(callback),
		state(State::Neutral), pressed(false), textSpacing(10.0f, 10.0f), autoHeight(false)
{
	text = new MultilineText(textSpacing + GetOffset(), sf::Vector2f(size.x - textSpacing.x * 2.0f, size.y - textSpacing.y * 2.0f));
	text->SetTextAlignment(Alignment(HorizontalAlign::Middle, VerticalAlign::Center));
}

Button::~Button()
{
	if (text != nullptr)
	{
		delete text;
		text = nullptr;
	}
}

void Button::Update(float delta)
{
	if (IsActive())
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
					callback.stringCallback(text->GetText());
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
	target.draw(*text, states);
}

void Button::LoadButtonGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border)
{
	LoadSlicedGraphic(tex);
	graphic->SetFrameSize(frameSize);
	graphic->SetSize(size);
	static_cast<SlicedGraphic*>(graphic)->SetBorder(border);
}

void Button::UpdateLayout()
{
	text->SetSize(sf::Vector2f(size.x - textSpacing.x * 2.0f, text->GetSize().y));
	if (autoHeight)
	{
		size.y = text->GetSize().y + textSpacing.y * 2.0f;
		UIObject::UpdateSize();
	}
}

void Button::SetActive(bool active)
{
	UIObject::SetActive(active);
	if (!active)
		SetState(State::Neutral);
}

void Button::SetSize(sf::Vector2f size)
{
	this->size = size;
	UpdateLayout();
	UIObject::UpdateSize();
}

void Button::SetTextSpacing(sf::Vector2f spacing)
{
	this->textSpacing = spacing;
	UpdateLayout();
}

void Button::SetAutoHeight(bool autoHeight)
{
	this->autoHeight = autoHeight;
	if (autoHeight)
		UpdateLayout();
}

void Button::SetState(State state)
{
	this->state = state;
	if (graphic != nullptr)
		graphic->SetFrame((int)state);
}
