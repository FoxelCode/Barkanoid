#pragma once

#include "Transformable.hpp"
#include "IUpdatable.hpp"
#include "Collider.hpp"
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

class GameObject : public Transformable, public sf::Drawable, IUpdatable
{
public:
	GameObject() {}
	~GameObject();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Update(float delta);

	virtual void Separate(sf::Vector2f separation) { Move(separation); }
	Collider* GetCollider() { return collider; }
	void SetTexture(sf::Texture* tex, float scale = 1.0f);
	void SetTextureRect(sf::IntRect rect);

protected:
	Collider* collider = nullptr;
	sf::Texture* texture;
	float textureScale;
	sf::Sprite sprite;
};