#include "Game/UI/LevelEntry.hpp"

#include "Engine/G.hpp"
#include "Graphics/SlicedGraphic.hpp"
#include "Game/Barkanoid.hpp"

const sf::Vector2f LevelEntry::padding = sf::Vector2f(10.0f, 10.0f);
const float LevelEntry::levelBottomSpacing = 8.0f;
const float LevelEntry::stageScoreWidth = 140.0f;
const float LevelEntry::stageScoreXSpacing = 16.0f;

LevelEntry::LevelEntry(const Level& level, ButtonStringCallback playButtonCallback, sf::Vector2f pos, sf::Vector2f size, Alignment align, ButtonStringCallback editButtonCallback)
	: UIObject(pos, size, align), playButtonCallback(playButtonCallback), editButtonCallback(editButtonCallback), editButton(nullptr)
{
	LoadSlicedGraphic(G::GetAssetManager()->GetTexture("button.png"));
	graphic->SetFrameSize(sf::Vector2f(18, 18));
	static_cast<SlicedGraphic*>(graphic)->SetBorder(sf::Vector2f(6, 6));
	graphic->SetFrame(4);

	sf::Vector2f curElementPos = padding + GetOffset();
	ScoreIO& scoreIO = dynamic_cast<Barkanoid*>(G::GetGame())->GetScoreIO();

	levelName = new MultilineText(curElementPos, sf::Vector2f(size.x - padding.x * 2.0f, 0.0f));
	levelName->SetParent(this);
	levelName->SetAutoHeight(true);
	levelName->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	levelName->GetFirstLine()->setCharacterSize(40);
	levelName->GetFirstLine()->setFillColor(sf::Color::Black);
	levelName->SetTextAlignment(Alignment(HorizontalAlign::Middle, VerticalAlign::Top));
	levelName->SetText(level.GetLevelName());
	curElementPos.y += levelName->GetSize().y;

	levelScore = new MultilineText(curElementPos, sf::Vector2f(size.x - padding.x * 2.0f, 0.0f));
	levelScore->SetParent(this);
	levelScore->SetAutoHeight(true);
	levelScore->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	levelScore->GetFirstLine()->setCharacterSize(40);
	levelScore->GetFirstLine()->setFillColor(sf::Color::Black);
	levelScore->SetTextAlignment(Alignment(HorizontalAlign::Middle, VerticalAlign::Top));
	int score = scoreIO.GetLevelScore(level.GetLevelName());
	if (score >= 0)
		levelScore->SetText(std::to_string(score));
	else
		levelScore->SetText("-");
	curElementPos.y += levelScore->GetSize().y + levelBottomSpacing;

	const std::vector<std::string> stageNames = level.GetStageNames();
	for (std::string stage : stageNames)
	{
		MultilineText* stageName = new MultilineText(curElementPos, sf::Vector2f(size.x - padding.x * 2.0f - stageScoreWidth - stageScoreXSpacing, 0.0f));
		stageName->SetParent(this);
		stageName->SetAutoHeight(true);
		stageName->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
		stageName->GetFirstLine()->setFillColor(sf::Color::Black);
		stageName->SetText(stage);
		this->stageNames.push_back(stageName);

		MultilineText* stageScore = new MultilineText(curElementPos + sf::Vector2f(size.x - padding.x * 2.0f, 0.0f),
			sf::Vector2f(stageScoreWidth, stageName->GetSize().y), Alignment(HorizontalAlign::Right, VerticalAlign::Top));
		stageScore->SetParent(this);
		stageScore->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
		stageScore->GetFirstLine()->setFillColor(sf::Color::Black);
		stageScore->SetTextAlignment(Alignment(HorizontalAlign::Right, VerticalAlign::Center));
		score = scoreIO.GetStageScore(level.GetLevelName(), stage);
		if (score >= 0)
			stageScore->SetText(std::to_string(score));
		else
			stageScore->SetText("-");
		this->stageScores.push_back(stageScore);

		curElementPos.y += stageName->GetSize().y;
	}

	float buttonWidth = size.x - padding.x * 2.0f;
	if (editButtonCallback != nullptr)
		buttonWidth /= 2.0f;

	playButton = new Button(curElementPos + GetPosition() + GetOffset(), sf::Vector2f(buttonWidth, 0.0f), (ButtonCallback)std::bind(&LevelEntry::PlayButtonPressed, this));
	playButton->SetParent(this);
	playButton->SetAutoHeight(true);
	playButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
	playButton->GetText()->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	playButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
	playButton->GetText()->SetAutoHeight(true);
	playButton->GetText()->SetText("Play");
	playButton->UpdateLayout();

	if (editButtonCallback != nullptr)
	{
		editButton = new Button(curElementPos + GetPosition() + GetOffset() + sf::Vector2f(buttonWidth + 1.0f, 0.0f), sf::Vector2f(buttonWidth - 1.0f, 0.0f), (ButtonCallback)std::bind(&LevelEntry::EditButtonPressed, this));
		editButton->SetParent(this);
		editButton->SetAutoHeight(true);
		editButton->LoadButtonGraphic(G::GetAssetManager()->GetTexture("button.png"), sf::Vector2f(18, 18), sf::Vector2f(6, 6));
		editButton->GetText()->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
		editButton->GetText()->GetFirstLine()->setFillColor(sf::Color::Black);
		editButton->GetText()->SetAutoHeight(true);
		editButton->GetText()->SetText("Edit");
		editButton->UpdateLayout();
	}
	curElementPos.y += playButton->GetSize().y;

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
	if (editButton != nullptr)
	{
		delete editButton;
		editButton = nullptr;
	}
	if (levelName != nullptr)
	{
		delete levelName;
		levelName = nullptr;
	}
	if (levelScore != nullptr)
	{
		delete levelScore;
		levelScore = nullptr;
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
	for (MultilineText* stageScore : stageScores)
	{
		if (stageScore != nullptr)
		{
			delete stageScore;
			stageScore = nullptr;
		}
	}
	stageScores.clear();
}

void LevelEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIObject::draw(target, states);
	target.draw(*playButton, states);
	if (editButton != nullptr)
		target.draw(*editButton, states);
	target.draw(*levelName, states);
	target.draw(*levelScore, states);
	for (const MultilineText* stageName : stageNames)
		target.draw(*stageName, states);
	for (const MultilineText* stageScore : stageScores)
		target.draw(*stageScore, states);
}

void LevelEntry::Update(float delta)
{
	playButton->Update(delta);
	if (editButton != nullptr)
		editButton->Update(delta);
}

void LevelEntry::PlayButtonPressed()
{
	playButtonCallback(levelName->GetText());
}

void LevelEntry::EditButtonPressed()
{
	editButtonCallback(levelName->GetText());
}
