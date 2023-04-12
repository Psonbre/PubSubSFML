#include "stdafx.h"
#include "Inputs.h"


const float Inputs::CONTROLLER_DEAD_ZONE = 20;

Inputs::Inputs()
{
	reset();
}

//Portée analogue -100 à 100
float Inputs::eliminateVibration(float analogInput)
{
	if (abs(analogInput) < CONTROLLER_DEAD_ZONE)
		return 0.0f;
	return analogInput;
}

void Inputs::reset()
{
	thrustMask = 0.0f;
	rotateMask = 0.0f;
	activeShipMask = -1;
	leftClick.x = leftClick.y = rightClick.x = rightClick.y = -1;
	choiceOfActorMask = ActorType::NONE;
}