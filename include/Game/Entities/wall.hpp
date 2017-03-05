#pragma once

#include "Engine/GameObject.hpp"

class Wall : public GameObject
{
public:
	Wall(sf::Vector2f pos, sf::Vector2f size);
};