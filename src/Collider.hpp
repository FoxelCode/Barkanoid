#pragma once

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

enum ColliderType
{
	AABB,
	Circle,
	List
};

class GameObject;

class Collider
{
public:
	Collider(GameObject* gameObject)
		: gameObject(gameObject) {};
	virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const {}

	virtual ColliderType GetType() { return ColliderType::AABB; }
	GameObject* GetGameObject() { return gameObject; }
	sf::Vector2f GetOffset() const { return offset; }

	void SetOffset(sf::Vector2f offset) { this->offset = offset; }
	
private:
	GameObject* gameObject;
	sf::Vector2f offset;
};