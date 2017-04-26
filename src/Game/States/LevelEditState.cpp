#include "Game/States/LevelEditState.hpp"

#include "Engine/G.hpp"
#include "Engine/Game.hpp"
#include "UI/MultilineText.hpp"
#include "UI/VerticalScrollArea.hpp"
#include "Game/UI/StageEditEntry.hpp"

const sf::Vector2f LevelEditState::padding = sf::Vector2f(10.0f, 10.0f);
const float LevelEditState::maxHeaderHeight = 100.0f;
const float LevelEditState::headerSpacing = 10.0f;

LevelEditState::LevelEditState(std::string levelName)
	: State(), levelName(levelName)
{
}

LevelEditState::~LevelEditState()
{
	if (level != nullptr)
	{
		delete level;
		level = nullptr;
	}
}

void LevelEditState::Init()
{
	level = new Level(G::GetAssetManager()->GetLevel(levelName));

	sf::Vector2f size = sf::Vector2f(GetGame()->GetSize());
	sf::Vector2f curElementPos = padding;

	MultilineText* levelNameHeader = new MultilineText(curElementPos, sf::Vector2f(size.x - padding.x * 2.0f, maxHeaderHeight));
	levelNameHeader->GetFirstLine()->setFont(*G::GetAssetManager()->GetFont("OneTrickPony.otf"));
	levelNameHeader->GetFirstLine()->setCharacterSize(40);
	levelNameHeader->GetFirstLine()->setFillColor(sf::Color::White);
	levelNameHeader->SetTextAlignment(Alignment(HorizontalAlign::Middle, VerticalAlign::Top));
	levelNameHeader->SetText(level->GetLevelName());
	Add(levelNameHeader);
	curElementPos.y += levelNameHeader->GetSize().y + headerSpacing;

	VerticalScrollArea* stageEntryArea = new VerticalScrollArea(curElementPos, size - curElementPos - padding);
	Add(stageEntryArea);

	const std::vector<std::string> stageNames = level->GetStageNames();
	for (const auto& stageName : stageNames)
	{
		StageEditEntry* stageEntry = new StageEditEntry(stageName, nullptr, sf::Vector2f(), sf::Vector2f(stageEntryArea->GetSize().x, 0.0f));
		Add(stageEntry);
		stageEntryArea->AddChild(stageEntry);
	}
}
