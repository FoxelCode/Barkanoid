#pragma once

#include <SFML/Graphics/Text.hpp>

#include "UI/UIObject.hpp"

class MultilineText : public UIObject
{
public:
	MultilineText(sf::Vector2f pos, sf::Vector2f size, Alignment align = Alignment());
	~MultilineText();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void SetText(std::string text);
	void SetTextAlignment(Alignment align);
	void SetAutoHeight(bool autoHeight);

	std::string GetText() { return text; }
	sf::Text* GetFirstLine() { return lines[0]; }

private:
	void UpdateLineLayout();
	void SetLineText(size_t line, std::string text);

	std::string text;
	Alignment textAlignment;
	bool autoHeight;
	std::vector<sf::Text*> lines;
};