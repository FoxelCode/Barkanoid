#include "Game/Entities/ParticleEmitter.hpp"

#include "Util/Random.hpp"
#include "Util/Math.hpp"

ParticleEmitter::ParticleEmitter(sf::Vector2f pos, sf::Texture* particleTexture,
	float launchVelocity, float velocityRandomRange,
	float lifetime, float lifetimeRandomRange, float gravity, bool fadeOut)
	: GameObject(pos), particleTexture(particleTexture),
	launchVelocity(launchVelocity), velocityRandomRange(velocityRandomRange),
	lifetime(lifetime), lifetimeRandomRange(lifetimeRandomRange),
	gravity(gravity), fadeOut(fadeOut)
{
}

void ParticleEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	for (const auto& particle : particles)
		target.draw(particle, states);
}

void ParticleEmitter::Update(float delta)
{
	for (auto it = particles.begin(); it != particles.end(); )
	{
		Particle& particle = (*it);

		particle.curLifetime += delta;
		if (particle.curLifetime > particle.lifetime)
		{
			it = particles.erase(it);
		}
		else
		{
			particle.velocity.y += gravity * delta;
			particle.setPosition(particle.getPosition() + particle.velocity * delta);
			particle.SetAlpha(255.0f - particle.curLifetime * particle.alphaDelta);
			it++;
		}
	}

	if (particles.empty())
		Kill();
}

void ParticleEmitter::Emit(size_t count)
{
	for (size_t i = 0U; i < count; i++)
	{
		Particle particle;
		float launchVel = launchVelocity + Random::Float(velocityRandomRange) - velocityRandomRange / 2.0f;
		float angle = Random::Float((float)PIELLO_DARKNESS_MY_OLD_FRIEND * 2.0f);
		particle.velocity = sf::Vector2f(cosf(angle) * launchVel, sinf(angle) * launchVel);
		particle.lifetime = Math::max(0.0f, lifetime + Random::Float(lifetimeRandomRange) - lifetimeRandomRange / 2.0f);
		particle.curLifetime = 0.0f;
		if (fadeOut)
			particle.alphaDelta = 255.0f / particle.lifetime;
		else
			particle.alphaDelta = 0.0f;
		particle.SetTexture(particleTexture);
		particles.push_back(particle);
	}
}
