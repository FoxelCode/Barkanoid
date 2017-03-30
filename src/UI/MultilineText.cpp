#include "UI/MultilineText.hpp"

#include "Util/StringUtil.hpp"

MultilineText::MultilineText(sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: UIObject(pos, size, align)
{
	sf::Text* firstLine = new sf::Text();
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
		wordLength = word.length();
		for (size_t c = 0; c < wordLength; c++)
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
					SetLineText(lineIndex, word.substr(0U, (c == 0) ? c : c - 1));
					word = word.substr(c - 1);
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
		}

		// Add the word to the current line
		currentLine += word;
		wordAddedToCurrentLine = true;

		// This and the next word should be divided by a space so add that
		currentLine += ' ';
		lineLength += spaceWidth;
	}

	// Finally, add whatever we have left in the line
	SetLineText(lineIndex, currentLine);
}

void MultilineText::SetLineText(size_t line, std::string text)
{
	// Add lines until we have enough of them
	while (line >= lines.size())
	{
		sf::Text* newLine = new sf::Text(text, *lines[0]->getFont(), lines[0]->getCharacterSize());
		newLine->setPosition(sf::Vector2f(0.0f, line * newLine->getFont()->getLineSpacing(newLine->getCharacterSize())));
		lines.push_back(newLine);
	}

	// Set the line's string
	lines[line]->setString(text);
}
