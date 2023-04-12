#pragma once
#include "ActorType.h"
struct Inputs
{
	static const float CONTROLLER_DEAD_ZONE;
	float thrustMask;
	float rotateMask;
	int activeShipMask;
	ActorType choiceOfActorMask;
	sf::Vector2f leftClick;
	sf::Vector2f rightClick;

	Inputs();
	void reset();
	//Portée analogue -100 à 100
	static float eliminateVibration(float analogInput);

	
};

