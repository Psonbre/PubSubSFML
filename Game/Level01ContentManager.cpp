#include "stdafx.h"
#include "Level01ContentManager.h"


Level01ContentManager::Level01ContentManager()
{
}


bool Level01ContentManager::loadContent()
{
	if (!backgroundT.loadFromFile("Assets\\Sprites\\Stars.jpg"))
	{
		return false;
	}

	if (!playerShipT.loadFromFile("Assets\\Sprites\\PlayerShip.png"))
	{
		return false;
	}
	if (!radiationT.loadFromFile("Assets\\Sprites\\Radiation.png")) 
		return false;
	if(!bombExplositionT.loadFromFile("Assets\\Sprites\\Bomb.png"))
		return false;
	if(!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
		return false;
	return true;
}
const sf::Texture& Level01ContentManager::getRadiationTexture() const
{
	return radiationT;
}
const sf::Texture& Level01ContentManager::getBombExplosionTexture() const
{
	return bombExplositionT;
}

const sf::Texture& Level01ContentManager::getBackgroundTexture() const
{
	return backgroundT;
}

const sf::Texture& Level01ContentManager::getPlayerShipTexture() const
{
	return playerShipT;
}

const sf::Font& Level01ContentManager::getFont() const
{
	return font;
}