#include "Game/UI/StageEditEntry.hpp"

#include "Engine/G.hpp"
#include "Graphics/SlicedGraphic.hpp"

const sf::Vector2f StageEditEntry::padding = sf::Vector2f(10, 10);
const float StageEditEntry::editButtonWidth = 80.0f;
const float StageEditEntry::editButtonSpacing = 10.0f;

StageEditEntry::StageEditEntry(std::string stageName, ButtonStringCallback editButtonCallback, sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: UIObject(pos, size, align)
{
	LoadSlicedGraphic(G::GetAssetManager()->GetTexture("button.png"));
	graphic->SetFrameSize(sf::Vector2f(18, 18));
	static_cast<SlicedGraphic*>(graphic)->SetBorder(sf::Vector2f(6, 6));
	graphic->SetFrame(4);

	this->stageName = new MultilineText(padding, sf::Vector2f(size.x - padding.x * 2.0f - editButtonWidth - editButtonSpacing, 0.0f));
	this->stageName->SetParent(this);
	this->stageName->SetAutoHeight(true);
	this->stageName->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	this->stageName->GetFirstLine()->setCharacterSize(40);
	this->stageName->GetFirstLine()->setFillColor(sf::Color::Black);
	this->stageName->SetText(stageName);

	editButton = new Button(sf::Vector2f(size.x - padding.x, padding.y), sf::Vector2f(editButtonWidth, this->stageName->GetSize().y),
		editButtonCallback, Alignment(HorizontalAlign::Right, VerticalAlign::Top));
	editButton->SetParent(this);
	editButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	editButton->GetText()->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	editButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	editButton->GetText()->SetText("Edit");

	SetSize(sf::Vector2f(size.x, this->stageName->GetSize().y + padding.y * 2.0f));
}

void StageEditEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIObject::draw(target, states);
	target.draw(*stageName, states);
	target.draw(*editButton, states);
}

void StageEditEntry::Update(float delta)
{
	GameObject::Update(delta);
}
