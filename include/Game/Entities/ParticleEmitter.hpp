#pragma once

#include "Engine/GameObject.hpp"
#include "Graphics/Graphic.hpp"

struct Particle;

class ParticleEmitter : public GameObject
{
public:
	ParticleEmitter(sf::Vector2f pos, sf::Texture* particleTexture, float launchVelocity, float velocityRandomRange, float lifetime, float lifetimeRandomRange, float gravity, bool fadeOut = true);
	~ParticleEmitter() {}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float delta);

	void Emit(size_t count);

private:
	std::vector<Particle> particles;

	sf::Texture* particleTexture;
	float launchVelocity;
	float velocityRandomRange;
	float lifetime;
	float lifetimeRandomRange;
	float gravity;
	bool fadeOut;
};

struct Particle : public Graphic
{
	Particle() : Graphic(Graphic::Alignment::Center) {}

	sf::Vector2f velocity;
	float lifetime;
	float curLifetime;
	float alphaDelta;
};