#include "Game/UI/LevelEntry.hpp"

#include "Engine/G.hpp"
#include "Graphics/SlicedGraphic.hpp"

const sf::Vector2f LevelEntry::padding = sf::Vector2f(10.0f, 10.0f);
const sf::Vector2f LevelEntry::playButtonSize = sf::Vector2f(70.0f, 40.0f);
const float LevelEntry::playButtonXSpacing = 10.0f;
const float LevelEntry::levelBottomSpacing = 10.0f;
const float LevelEntry::stageXOffset = 16.0f;

LevelEntry::LevelEntry(const Level& level, ButtonStringCallback playButtonCallback, sf::Vector2f pos, sf::Vector2f size, Alignment align)
	: UIObject(pos, size, align), playButtonCallback(playButtonCallback)
{
	LoadSlicedGraphic(G::GetAssetManager()->GetTexture("button.png"));
	graphic->SetFrameSize(sf::Vector2f(18, 18));
	static_cast<SlicedGraphic*>(graphic)->SetBorder(sf::Vector2f(6, 6));
	graphic->SetFrame(4);

	sf::Vector2f curElementPos = padding + GetOffset();

	levelName = new MultilineText(curElementPos, sf::Vector2f(size.x - padding.x * 2.0f - playButtonSize.x - playButtonXSpacing, 0.0f));
	levelName->SetParent(this);
	levelName->SetAutoHeight(true);
	levelName->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	levelName->GetFirstLine()->setCharacterSize(40);
	levelName->GetFirstLine()->setFillColor(sf::Color::Black);
	levelName->SetText(level.GetLevelName());
	curElementPos.y += levelName->GetSize().y + levelBottomSpacing;

	playButton = new Button(sf::Vector2f(size.x - padding.x, padding.y) + GetPosition() + GetOffset(), playButtonSize, (ButtonCallback)std::bind(&LevelEntry::PlayButtonPressed, this), Alignment(HorizontalAlign::Right, VerticalAlign::Top));
	playButton->SetParent(this);
	playButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	playButton->GetText()->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	playButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	playButton->GetText()->SetText("Play");

	const std::vector<std::string> stageNames = level.GetStageNames();
	for (std::string stage : stageNames)
	{
		MultilineText* stageName = new MultilineText(curElementPos + sf::Vector2f(stageXOffset, 0.0f), sf::Vector2f(size.x - padding.x * 2.0f - stageXOffset, 0.0f));
		stageName->SetParent(this);
		stageName->SetAutoHeight(true);
		stageName->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
		stageName->GetFirstLine()->setFillColor(sf::Color::Black);
		stageName->SetText(stage);
		this->stageNames.push_back(stageName);
		curElementPos.y += stageName->GetSize().y;
	}

	curElementPos.y += padding.y;
	SetSize(sf::Vector2f(size.x, curElementPos.y));
}

LevelEntry::~LevelEntry()
{
	if (playButton != nullptr)
	{
		delete playButton;
		playButton = nullptr;
	}
	if (levelName != nullptr)
	{
		delete levelName;
		levelName = nullptr;
	}
	for (MultilineText* stageName : stageNames)
	{
		if (stageName != nullptr)
		{
			delete stageName;
			stageName = nullptr;
		}
	}
	stageNames.clear();
}

void LevelEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIObject::draw(target, states);
	target.draw(*playButton, states);
	target.draw(*levelName, states);
	for (const MultilineText* stageName : stageNames)
		target.draw(*stageName, states);
}

void LevelEntry::Update(float delta)
{
	playButton->Update(delta);
}

void LevelEntry::PlayButtonPressed()
{
	playButtonCallback(levelName->GetText());
}
