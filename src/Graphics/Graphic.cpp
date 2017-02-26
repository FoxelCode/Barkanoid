#include "Graphics/Graphic.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>

Graphic::Graphic()
	: colour(255, 255, 255, 255)
{
}

void Graphic::SetSize(sf::Vector2f size)
{
	this->size = size;
	UpdateVertices();
}

void Graphic::SetTexture(sf::Texture* tex)
{
	texture = tex;
	frameSize = sf::Vector2f((float)tex->getSize().x, (float)tex->getSize().y);
	SetSize(sf::Vector2f(tex->getSize()));
}

void Graphic::SetTextureRepeating(bool repeating)
{
	texture->setRepeated(repeating);
}

void Graphic::SetColour(sf::Color colour)
{
	this->colour = colour;
	for (size_t i = 0; i < vertices.getVertexCount(); i++)
		vertices[i].color = colour;
}

void Graphic::SetFrameSize(sf::Vector2f frameSize)
{
	this->frameSize = frameSize;
	SetSize(frameSize);
}

void Graphic::SetFrame(int frame)
{
	int columns = texture->getSize().x / (int)frameSize.x;
	framePos = sf::Vector2f((frame % columns) * frameSize.x, (frame / columns) * frameSize.y);
	UpdateVertices();
}

void Graphic::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = texture;
	target.draw(vertices, states);
}

void Graphic::UpdateVertices()
{
	vertices = sf::VertexArray(sf::Quads, 4);

	vertices[0].position = sf::Vector2f(0, 0);
	vertices[1].position = sf::Vector2f(size.x, 0);
	vertices[2].position = sf::Vector2f(size.x, size.y);
	vertices[3].position = sf::Vector2f(0, size.y);

	if (texture->isRepeated())
	{
		sf::Vector2f frameAmount = sf::Vector2f(size.x / frameSize.x, size.y / frameSize.y);
		vertices[0].texCoords = sf::Vector2f(framePos.x, framePos.y);
		vertices[1].texCoords = sf::Vector2f(framePos.x + frameAmount.x * frameSize.x, framePos.y);
		vertices[2].texCoords = sf::Vector2f(framePos.x + frameAmount.x * frameSize.x, framePos.y + frameAmount.y * frameSize.y);
		vertices[3].texCoords = sf::Vector2f(framePos.x, framePos.y + frameAmount.y * frameSize.y);
	}
	else
	{
		vertices[0].texCoords = sf::Vector2f(framePos.x, framePos.y);
		vertices[1].texCoords = sf::Vector2f(framePos.x + frameSize.x, framePos.y);
		vertices[2].texCoords = sf::Vector2f(framePos.x + frameSize.x, framePos.y + frameSize.y);
		vertices[3].texCoords = sf::Vector2f(framePos.x, framePos.y + frameSize.y);
	}

	vertices[0].color = colour;
	vertices[1].color = colour;
	vertices[2].color = colour;
	vertices[3].color = colour;
}
