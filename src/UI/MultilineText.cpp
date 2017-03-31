#include "UI/MultilineText.hpp"

#include "Util/StringUtil.hpp"

MultilineText::MultilineText(sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: UIObject(pos, size, align), autoHeight(false)
{
	sf::Text* firstLine = new sf::Text();
	firstLine->setPosition(GetOffset());
	lines.push_back(firstLine);
}

MultilineText::~MultilineText()
{
	for (sf::Text* line : lines)
	{
		if (line != nullptr)
		{
			delete line;
			line = nullptr;
		}
	}
	lines.clear();
}

void MultilineText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	for (const sf::Text* line : lines)
		target.draw(*line, states);
}

void MultilineText::SetText(std::string text)
{
	this->text = text;

	// Font attributes
	const sf::Font* font = lines[0]->getFont();
	size_t charSize = lines[0]->getCharacterSize();
	bool bold = (lines[0]->getStyle() & sf::Text::Style::Bold) != 0;
	float spaceWidth = font->getGlyph(L' ', charSize, bold).advance;

	// Character iteration variables
	std::vector<std::string> words = StringUtil::Split(text, " ");
	std::string currentLine;
	size_t lineIndex = 0U;
	sf::Uint32 prevChar = 0U;
	float lineLength = 0.0f;
	size_t wordLength = 0U;
	bool wordAddedToCurrentLine = false;

	for (std::string word : words)
	{
		// If there's already a word on the current line, take into account the space that should be inserted between the two words
		if (wordAddedToCurrentLine)
			lineLength += spaceWidth;

		wordLength = word.length();
		for (size_t c = 0; c < wordLength; )
		{
			// Kerning offset
			lineLength += font->getKerning(prevChar, word[c], charSize);
			prevChar = word[c];

			// Add the advance offset of the glyph
			lineLength += font->getGlyph(word[c], charSize, bold).advance;

			// Check if the current line is going off bounds
			if (lineLength >= size.x)
			{
				// If the whole word is wider than the bounds, split the word
				if (!wordAddedToCurrentLine)
				{
					SetLineText(lineIndex, word.substr(0U, c));
					word = word.substr(c);
				}
				// Otherwise the current word goes on the next line
				else
				{
					SetLineText(lineIndex, currentLine);
				}

				// Reset the iteration over the current word
				wordLength = word.length();
				c = 0;

				// Reset line specific iteration variables
				currentLine = "";
				prevChar = 0U;
				lineLength = 0.0f;
				wordAddedToCurrentLine = false;
				lineIndex++;
			}
			// If the line didn't go off bounds, move on to the next character
			else
				c++;
		}

		// If there's a word already on this line, add a space between it and this new one
		if (wordAddedToCurrentLine)
			currentLine += ' ';

		// Add the word to the current line
		currentLine += word;
		wordAddedToCurrentLine = true;
	}

	// Finally, add whatever we have left in the line
	SetLineText(lineIndex, currentLine);

	// Remove extra lines if there are some
	while (lines.size() > (lineIndex + 1))
	{
		sf::Text* toRemove = lines[lines.size() - 1];
		if (toRemove != nullptr)
		{
			delete toRemove;
			toRemove = nullptr;
		}
		lines.pop_back();
	}

	// Update the lines with the new text
	UpdateLineLayout();
}

void MultilineText::SetTextAlignment(Alignment align)
{
	this->textAlignment = align;
	UpdateLineLayout();
}

void MultilineText::SetAutoHeight(bool autoHeight)
{
	this->autoHeight = autoHeight;
	if (autoHeight)
		UpdateLineLayout();
}

void MultilineText::UpdateLineLayout()
{
	if (lines[0]->getFont() == nullptr)
		return;

	float lineHeight = lines[0]->getFont()->getLineSpacing(lines[0]->getCharacterSize());

	// If autoHeight is set, set the height of the UIObject to the height of the lines
	if (autoHeight)
		SetSize(sf::Vector2f(size.x, lines.size() * lineHeight));

	// Set the starting height for the lines depending on vertical alignment
	float startHeight = -lines[0]->getLocalBounds().top / 2.0f;
	if (!autoHeight)	// No use aligning vertically if the bounds are exactly the height of the lines
	{
		switch (textAlignment.vertical)
		{
		case VerticalAlign::Top:
			break;
		case VerticalAlign::Center:
			startHeight += size.y / 2.0f - ((float)lines.size() / 2.0f) * lineHeight;
			break;
		case VerticalAlign::Bottom:
			startHeight += size.y - (float)lines.size() * lineHeight;
			break;
		}
	}

	size_t lineCount = lines.size();
	for (size_t i = 0; i < lineCount; i++)
	{
		sf::Vector2f linePos = sf::Vector2f(0.0f, startHeight + i * lineHeight) + GetOffset();

		// Set the line's X position using horizontal align
		switch (textAlignment.horizontal)
		{
		case HorizontalAlign::Left:
			break;
		case HorizontalAlign::Middle:
			linePos.x += size.x / 2.0f - lines[i]->getGlobalBounds().width / 2.0f;
			break;
		case HorizontalAlign::Right:
			linePos.x += size.x - lines[i]->getGlobalBounds().width;
			break;
		}

		lines[i]->setPosition(linePos);
	}
}

void MultilineText::SetLineText(size_t line, std::string text)
{
	// Add lines until we have enough of them
	while (line >= lines.size())
	{
		sf::Text* newLine = new sf::Text(text, *lines[0]->getFont(), lines[0]->getCharacterSize());
		newLine->setPosition(sf::Vector2f(0.0f, line * newLine->getFont()->getLineSpacing(newLine->getCharacterSize())) + GetOffset());
		newLine->setFillColor(lines[0]->getFillColor());
		lines.push_back(newLine);
	}

	// Set the line's string
	lines[line]->setString(text);
}
