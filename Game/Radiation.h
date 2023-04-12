#pragma once
#include "GameObject.h"

class Radiation :
    public GameObject
{
	static const float MAX_SCALE_FACTOR;
public:
	Radiation();
	virtual void activate()override;
	virtual bool init(const ContentManager& contentManager) override;	
	virtual bool update(float deltaT) override;
	void trigger();
	int getForce() const;
private:
	float scaleFactor;
	float multiplicator;
	int force;
};

