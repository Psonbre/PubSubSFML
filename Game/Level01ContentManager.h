	#pragma once
#include "ContentManager.h"
class Level01ContentManager : public ContentManager
{
public:
	Level01ContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getPlayerShipTexture() const;
	const sf::Texture& getBombExplosionTexture() const;
	const sf::Texture& getRadiationTexture() const;
	const sf::Font& getFont() const;
private:
	sf::Texture backgroundT;
	sf::Texture playerShipT;
	sf::Texture radiationT;
	sf::Font font;
	sf::Texture bombExplositionT;
};



