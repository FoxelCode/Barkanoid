#include "Graphics/SlicedGraphic.hpp"

SlicedGraphic::SlicedGraphic(Alignment align)
	: Graphic(align)
{
}

void SlicedGraphic::SetBorder(sf::Vector2f border)
{
	this->border = border;
	UpdateVertices();
}

void SlicedGraphic::UpdateVertices()
{
	sf::Vector2f offset;
	if (align == Alignment::TopLeft)
		offset = size / 2.0f;

	// Slice on both axes
	if (border.x != 0 && border.y != 0)
	{
		/*
			0,	1,	2,	3,
			4,	5,	6,	7,
			8,	9,	10,	11,
			12,	13,	14,	15
		*/
		sf::Vector2f vertPositions[16];
		sf::Vector2f vertUVs[16];
		float vertPosX[4] = { 0, border.x, size.x - border.x, size.x };
		float vertPosY[4] = { 0, border.y, size.y - border.y, size.y };
		float vertUVX[4] = { framePos.x, framePos.x + border.x, framePos.x + frameSize.x - border.x, framePos.x + frameSize.x };
		float vertUVY[4] = { framePos.y, framePos.y + border.y, framePos.y + frameSize.y - border.y, framePos.y + frameSize.y };
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				vertPositions[y * 4 + x] = sf::Vector2f(vertPosX[x], vertPosY[y]) + offset;
				vertUVs[y * 4 + x] = sf::Vector2f(vertUVX[x], vertUVY[y]);
			}
		}

		// Create 3 rows of TriangleStrips
		int vertOrder[24] = { 0, 4, 1, 5, 2, 6, 3, 7,
							  7, 11, 6, 10, 5, 9, 4, 8,
							  8, 12, 9, 13, 10, 14, 11, 15 };
		vertices = sf::VertexArray(sf::TriangleStrip, 24);
		for (int i = 0; i < 24; i++)
		{
			vertices[i].position = vertPositions[vertOrder[i]];
			vertices[i].texCoords = vertUVs[vertOrder[i]];
		}
	}

	// Slice on horizontal axis
	else if (border.x != 0 && border.y == 0)
	{
		/*
		0,	1,	2,	3,
		4,	5,	6,	7
		*/
		sf::Vector2f vertPositions[8];
		sf::Vector2f vertUVs[8];
		float vertPosX[4] = { 0, border.x, size.x - border.x, size.x };
		float vertPosY[2] = { 0, size.y };
		float vertUVX[4] = { framePos.x, framePos.x + border.x, framePos.x + frameSize.x - border.x, framePos.x + frameSize.x };
		float vertUVY[2] = { framePos.y, framePos.y + frameSize.y };
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				vertPositions[y * 4 + x] = sf::Vector2f(vertPosX[x], vertPosY[y]) + offset;
				vertUVs[y * 4 + x] = sf::Vector2f(vertUVX[x], vertUVY[y]);
			}
		}

		// Create 1 row of TriangleStrip
		int vertOrder[8] = { 0, 4, 1, 5, 2, 6, 3, 7 };
		vertices = sf::VertexArray(sf::TriangleStrip, 8);
		for (int i = 0; i < 8; i++)
		{
			vertices[i].position = vertPositions[vertOrder[i]];
			vertices[i].texCoords = vertUVs[vertOrder[i]];
		}
	}

	// Slice on vertical axis
	else if (border.x == 0 && border.y != 0)
	{
		/*
		0,	1,
		2,	3,
		4,	5,
		6,	7
		*/
		sf::Vector2f vertPositions[8];
		sf::Vector2f vertUVs[8];
		float vertPosX[2] = { 0, size.x };
		float vertPosY[4] = { 0, border.y, size.y - border.y, size.y };
		float vertUVX[2] = { framePos.x, framePos.x + frameSize.x };
		float vertUVY[4] = { framePos.y, framePos.y + border.y, framePos.y + frameSize.y - border.y, framePos.y + frameSize.y };
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				vertPositions[y * 2 + x] = sf::Vector2f(vertPosX[x], vertPosY[y]) + offset;
				vertUVs[y * 2 + x] = sf::Vector2f(vertUVX[x], vertUVY[y]);
			}
		}

		// Create 1 column of TriangleStrip
		int vertOrder[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		vertices = sf::VertexArray(sf::TriangleStrip, 8);
		for (int i = 0; i < 8; i++)
		{
			vertices[i].position = vertPositions[vertOrder[i]];
			vertices[i].texCoords = vertUVs[vertOrder[i]];
		}
	}

	// If no border was given, update the vertices with the simpler function in Graphic (4 vertices)
	else
	{
		Graphic::UpdateVertices();
	}
}
