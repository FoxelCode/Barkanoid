#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Graphic : public sf::Drawable, public sf::Transformable
{
public:
	enum Alignment
	{
		TopLeft,
		Center
	};

	Graphic(Alignment align = Alignment::TopLeft);

	void SetSize(sf::Vector2f size);
	void SetTexture(sf::Texture* tex);
	void SetTextureRepeating(bool repeating);
	void SetColour(sf::Color colour);
	void SetAlpha(float alpha);
	void SetFrameSize(sf::Vector2f frameSize);
	void SetFrame(int frame);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	virtual void UpdateVertices();
	virtual void UpdateVertPositions();
	virtual void UpdateVertUVs();
	virtual void UpdateVertColours();

	Alignment align;
	sf::Vector2f size;
	sf::VertexArray vertices;
	sf::Texture* texture;
	sf::Vector2f framePos;
	sf::Vector2f frameSize;
	sf::Color colour;
};