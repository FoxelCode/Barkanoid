#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include "Transform.hpp"
#include "IUpdatable.hpp"
#include "Collision/Collider.hpp"
#include "Graphics/Graphic.hpp"

class GameObject : public Transform, public sf::Drawable, IUpdatable
{
public:
	GameObject() {}
	GameObject(sf::Vector2f pos) { SetPosition(pos); }
	virtual ~GameObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void DrawCollider(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Update(float delta);

	virtual void Separate(sf::Vector2f separation) { Move(separation); }
	virtual void Collided(GameObject* other) {};

	void LoadGraphic(sf::Texture* tex);
	void LoadSlicedGraphic(sf::Texture* tex);

	sf::Vector2f GetVelocity() const { return velocity; }
	sf::Vector2f GetTarget(float delta) const { return GetPosition() + velocity * delta; }
	Collider* GetCollider() { return collider; }

	virtual void Kill() { alive = false; }
	bool IsAlive() const { return alive; }
	void SetActive(bool v) { active = v; }
	bool IsActive() const { return active; }

protected:
	Collider* collider = nullptr;
	Graphic* graphic = nullptr;

	sf::Vector2f velocity = sf::Vector2f();

private:
	bool alive = true;
	bool active = true;
};