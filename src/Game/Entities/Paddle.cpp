#include "Game/Entities/Paddle.hpp"

#include "Collision/AABBCollider.hpp"
#include "Engine/G.hpp"
#include "Engine/Input.hpp"
#include "Graphics/SlicedGraphic.hpp"
#include "Game/Entities/Ball.hpp"
#include "Util/Tween.hpp"

Paddle::Paddle(sf::Vector2f pos)
	: GameObject(pos), angleRange(140.0f * ((float)PIELLO_DARKNESS_MY_OLD_FRIEND / 180.0f)), widthBounds(32.0f, 200.0f), magnetic(false)
{
	size = sf::Vector2f(60.0f, 12.0f);
	collider = new AABBCollider(this, sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f), size);

	tween = new Tween::TweenInstance(Ease::Type::QuadOut, 0.0f, 1.0f, 0.15f,
		[this](float v) { graphic->setScale(1.0f + v * 0.3f, 1.0f - v * 0.4f); }, nullptr, Tween::Type::Boomerang);
	tween->Finish();
	Tween::Run(tween);

	LoadSlicedGraphic(G::GetAssetManager()->GetTexture("paddle.png"), Graphic::Alignment::Center);
	static_cast<SlicedGraphic*>(graphic)->SetBorder(sf::Vector2f(12, 0));
	SetWidth(size.x);
}

Paddle::~Paddle()
{
	if (tween != nullptr)
	{
		Tween::RemoveTween(tween);
		delete tween;
		tween = nullptr;
	}
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(GetPosition());
	target.draw(*graphic, states);
}

void Paddle::Update(float delta)
{
	sf::Vector2f mouseDelta = sf::Vector2f(Input::GetMouseDelta().x, 0.0f);
	Move(mouseDelta);
	float paddleX = Math::clamp(GetPosition().x, horizontalRange.x + size.x / 2.0f, horizontalRange.y - size.x / 2.0f);
	SetPosition(paddleX, GetPosition().y);

	for each (auto ball in attachedBalls)
		ball.first->SetPosition(GetPosition().x + ball.second, ball.first->GetPosition().y);

	if (Input::MousePressed(sf::Mouse::Button::Left))
	{
		for each (auto ball in attachedBalls)
		{
			ball.first->SetMoving(true);
		}
		attachedBalls.clear();
	}
}

void Paddle::Collided(GameObject* other)
{
	if (dynamic_cast<Ball*>(other))
	{
		tween->Reset();
		if (magnetic)
			AttachBall(reinterpret_cast<Ball*>(other));
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

float Paddle::GetReflectionAngle(sf::Vector2f pos)
{
	float dx = pos.x - GetPosition().x;
	dx = Math::clamp(dx, -size.x / 2.0f, size.x / 2.0f);
	dx /= size.x / 2.0f;
	return -(float)PIELLO_DARKNESS_MY_OLD_FRIEND / 2.0f + dx * (angleRange / 2.0f);
}

void Paddle::AttachBall(Ball* ball)
{
	attachedBalls.push_back(std::make_pair(ball, ball->GetPosition().x - GetPosition().x));
	ball->SetAngle((float)PIELLO_DARKNESS_MY_OLD_FRIEND / 2.0f);
	ball->SetMoving(false);
	ball->SetPosition(ball->GetPosition().x, GetPosition().y - size.y / 2.0f - ball->GetCollider()->GetBounds().width / 2.0f);
}

void Paddle::AddWidth(float width)
{
	size.x += width;
	size.x = Math::clamp(size.x, widthBounds.x, widthBounds.y);
	SetWidth(size.x);
}

void Paddle::Reset()
{
	attachedBalls.clear();
}
