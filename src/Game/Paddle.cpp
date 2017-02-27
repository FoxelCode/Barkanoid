#include "Game/Paddle.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Engine/Input.hpp"
#include "Graphics/SlicedGraphic.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: GameObject(pos), angleRange(160.0f)
{
	size = sf::Vector2f(60.0f, 12.0f);
	collider = new AABBCollider(this, sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f), size);

	LoadSlicedGraphic(G::GetAssetManager()->GetTexture("paddle.png"));
	static_cast<SlicedGraphic*>(graphic)->SetBorder(sf::Vector2f(12, 0));
	graphic->SetSize(size);
	graphic->setPosition(-size / 2.0f);

	SetWidth(size.x);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(*graphic, states);
	target.draw(leftSide, states);
	target.draw(rightSide, states);
}

void Paddle::Update(float delta)
{
	sf::Vector2f mousePos = sf::Vector2f((float)Input::GetMousePosition().x, GetPosition().y);
	sf::Vector2f mouseDelta = mousePos - GetPosition();

	Move(mouseDelta);
	float paddleX = Math::clamp(GetPosition().x, horizontalRange.x + size.x / 2.0f, horizontalRange.y - size.x / 2.0f);
	SetPosition(paddleX, GetPosition().y);

	for each (auto ball in attachedBalls)
		ball.first->SetPosition(GetPosition().x + ball.second, ball.first->GetPosition().y);

	if (Input::MouseJustPressed(sf::Mouse::Button::Left))
	{
		for each (auto ball in attachedBalls)
		{
			ball.first->SetMoving(true);
		}
		attachedBalls.clear();
	}
}

void Paddle::SetWidth(float width)
{
	size.x = width;
	AABBCollider* coll = static_cast<AABBCollider*>(collider);
	coll->SetOffset(sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f));
	coll->setSize(size);

	graphic->SetSize(size);
}

float Paddle::GetReflectionScalar(sf::Vector2f pos)
{
	return fmaxf(fminf((pos.x - GetPosition().x) / size.x, 1.0f), -1.0f);
}

void Paddle::AttachBall(Ball* ball)
{
	attachedBalls.push_back(std::make_pair(ball, ball->GetPosition().x - GetPosition().x));
	ball->SetAngle((float)PIELLO_DARKNESS_MY_OLD_FRIEND / 2.0f);
	ball->SetMoving(false);
	ball->SetPosition(ball->GetPosition().x, GetPosition().y - size.y / 2.0f - ball->GetRadius());
}