#include "stdafx.h"
#include "Radiation.h"
#include "Level01ContentManager.h"
#include "Publisher.h"
#include <iostream>


const float Radiation::MAX_SCALE_FACTOR = 1.5f;

Radiation::Radiation()
  : GameObject()
  , scaleFactor(1.0f)
  , multiplicator(1.0f)
{
  force = rand() % 50 + 1;
}


void Radiation::activate()
{
  scaleFactor = 1.0f;
  multiplicator = 0.0f;
  GameObject::activate();
}

bool Radiation::init(const ContentManager& contentManager)
{
  const Level01ContentManager& manager = (const Level01ContentManager&)contentManager;
  setTexture(manager.getRadiationTexture());
  setOrigin(getTexture()->getSize().x / 2.0f, getTexture()->getSize().y / 2.0f);
  return GameObject::init(contentManager);
}

bool Radiation::update(float deltaT)
{
  if (!isActive())
    return false;

  // La radiation grossit d'abord...
  scaleFactor += 0.003f * multiplicator;
  if (scaleFactor < 0.0f)
    deactivate();
  else if (scaleFactor > MAX_SCALE_FACTOR && multiplicator > 0)
  {
    // ... puis rétrécit rapidement
    // C'est ici qu'elle fait son action
    // A COMPLETER
    Publisher::notifySubscribers(Event::RADIATION,this);
    multiplicator = -3.0f;
  }
  setScale(sf::Vector2f(scaleFactor, scaleFactor));
  return GameObject::update(deltaT);
}

int Radiation::getForce() const
{
  return force;
}

void Radiation::trigger()
{
  multiplicator = 1.0f;
}