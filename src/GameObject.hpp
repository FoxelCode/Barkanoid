#pragma once

#include "Transform.hpp"
#include "IUpdatable.hpp"
#include "Collider.hpp"
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

class GameObject : public Transform, public sf::Drawable, IUpdatable
{
public:
	GameObject() {}
	GameObject(sf::Vector2f pos) { SetPosition(pos); }
	~GameObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Update(float delta);

	virtual void Separate(sf::Vector2f separation) { Move(separation); }
	virtual void Collided() {};

	virtual void Kill() { alive = false; }
	bool IsAlive() { return alive; }
	Collider* GetCollider() { return collider; }
	void SetTexture(sf::Texture* tex, float scale = 1.0f);
	void SetTextureRect(sf::IntRect rect);
	void SetFrameSize(sf::Vector2u frameSize) { this->frameSize = frameSize; }
	void SetFrame(int frame);

protected:
	Collider* collider = nullptr;
	sf::Texture* texture;
	float textureScale;
	sf::Sprite sprite;
	sf::Vector2u frameSize;

private:
	bool alive = true;
};