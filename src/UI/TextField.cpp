#include "UI/TextField.hpp"

#include "Graphics/SlicedGraphic.hpp"
#include "Engine/Input.hpp"
#include "Util/Math.hpp"

TextField::TextField(sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: UIObject(pos, size, align), state(State::OutOfFocus), cursor(sf::Vector2f(1.0f, size.y)), cursorBlinkTime(0.5f), cursorBlinkTimer(0.0f), cursorVisible(true)
{
	cursor.setFillColor(sf::Color::Black);
}

void TextField::Update(float delta)
{
	UIObject::Update(delta);

	bool hovering = Math::contains(sf::Vector2f(Input::GetMousePosition()), collider->GetBounds());

	switch (state)
	{
	case State::OutOfFocus:
		if (hovering && Input::MouseJustReleased(sf::Mouse::Left))
			SetState(State::Focused);
		break;

	case State::Focused:
		std::string textEntered = Input::GetTextEntered();
		if (!textEntered.empty())
			TextEntered(textEntered);

		cursorBlinkTimer += delta;
		if (cursorBlinkTimer >= cursorBlinkTime)
		{
			cursorBlinkTimer -= cursorBlinkTime;
			cursorVisible = !cursorVisible;
		}

		if (!hovering && Input::MouseJustReleased(sf::Mouse::Left))
			SetState(State::OutOfFocus);
		break;
	}
}

void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIObject::draw(target, states);
	states.transform.translate(GetPosition());
	target.draw(text, states);
	if (state == State::Focused && cursorVisible)
		target.draw(cursor, states);
}

void TextField::LoadTextFieldGraphic(sf::Texture* tex, sf::Vector2f frameSize, sf::Vector2f border)
{
	LoadSlicedGraphic(tex);
	graphic->SetFrameSize(frameSize);
	graphic->SetSize(size);
	static_cast<SlicedGraphic*>(graphic)->SetBorder(border);
}

void TextField::UpdateLayout()
{
	bool textEmpty = text.getString().isEmpty();
	if (textEmpty)
		text.setString("0");
	text.setPosition(sf::Vector2f(0.0f, size.y / 2.0f - text.getGlobalBounds().height));
	if (textEmpty)
		text.setString("");
}

void TextField::SetState(State state)
{
	this->state = state;
	if (state == State::Focused)
	{
		cursorBlinkTimer = 0.0f;
		cursorVisible = true;
	}
}

void TextField::TextEntered(std::string str)
{
	std::string textStr = text.getString();
	for each (char c in str)
	{
		if (c == 8)
		{
			if (textStr.size() > 0)
				textStr.pop_back();
		}
		else if (c >= 20)
		{
			textStr += c;
		}
	}
	text.setString(textStr);
	cursor.setPosition(GetOffset() + sf::Vector2f(text.getGlobalBounds().width, 0.0f));
	cursorBlinkTimer = 0.0f;
	cursorVisible = true;
}
