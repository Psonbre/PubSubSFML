#pragma once
#include "GameObject.h"
#include "Subscriber.h"

/// <summary>
/// Classe qui illustre de mani�re logique le vaisseau du joueur dans le jeu Asteroid
/// Pour le moment, on a que le d�placement du vaisseau.  Il peut pivoter et se d�placer
/// Par pouss�e avant.  Il garde toujours son inertie vectorielle.
/// </summary>
class PlayerShip : public GameObject, public Subscriber
{
	static const float MAX_SPEED;
public:
	PlayerShip();
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool init(const ContentManager& contentManager) override;
	const sf::Vector2f& getVectorialThrust() const;
	void notify(Event event, const void* data) override;
	bool update(float elapsedTime, float thrustValue, float rotationValue);
	void activate() override;
	void deactivate() override;
private:
	void setMaximumThrust();
	void handleOutOfBoundsPosition();
	
	sf::Vector2f vectorialThrust;
	float shipThrust;
	sf::Text text;
	int lifePoints;

};


