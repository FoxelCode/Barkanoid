#include "Level.hpp"

#include "ListCollider.hpp"

Level::Level(sf::Vector2f pos)
	: GameObject(pos)
{
	collider = new ListCollider(this);
	collider->SetOffset(pos);

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			AddBrick(new Brick(sf::Vector2f(x * 32.0f, y * 16.0f), Palette::Colours[y + 1]));
		}
	}
}

void Level::Update(float delta)
{
	for (int i = 0; i < bricks.size(); )
	{
		if (!bricks[i]->IsAlive())
		{
			Brick* toErase = bricks[i];
			RemoveBrick(toErase);
			delete toErase;
		}
		else
		{
			i++;
		}
	}
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	for each (Brick* brick in bricks)
	{
		target.draw(*brick, states);
	}
}

void Level::AddBrick(Brick* brick)
{
	bricks.push_back(brick);
	static_cast<ListCollider*>(collider)->AddCollider(brick->GetCollider());
}

void Level::RemoveBrick(Brick* brick)
{
	for (auto it = bricks.begin(); it != bricks.end(); it++)
	{
		if ((*it) == brick)
		{
			bricks.erase(it);
			break;
		}
	}
	static_cast<ListCollider*>(collider)->RemoveCollider(brick->GetCollider());
}
