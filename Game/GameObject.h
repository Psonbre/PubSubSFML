#pragma once

class ContentManager;
class GameObject : public sf::Sprite
{
public:
	GameObject();
	GameObject(const GameObject& src);
	GameObject& operator=(const GameObject& rhs);
	virtual void draw(sf::RenderWindow& window) const;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition);
	virtual bool init(const ContentManager& contentManager);
	virtual bool update(float deltaT);
	virtual void activate();
	virtual void deactivate();
	bool isActive() const;
	bool collidesWith(const GameObject& other) const;
	bool collidesWith(const sf::Vector2f& position) const;


	float getRotationAngleInRadians() const;
	void setRotationAngleRadians(const float angle);
	virtual void rotateInRadians(const float angle);

protected:
	float getAngleWith(const GameObject& other) const;
	bool active;
};

