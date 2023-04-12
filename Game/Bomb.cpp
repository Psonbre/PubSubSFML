#include "stdafx.h"
#include "Bomb.h"
#include "BombIdleAnimation.h"
#include "BombExplosionAnimation.h"
#include "game.h"
#include "Publisher.h"
#include <iostream>
const int Bomb::BOMB_RANGE = 750;

bool Bomb::init(const ContentManager& contentManager)
{
  // Initialisation des animations ici.
  currentState = AnimationState::BOMB_IDLE;

  // Ajout des animations
  bool retval = addAnimation<AnimationState::BOMB_IDLE, BombIdleAnimation>(contentManager);
  retval = addAnimation<AnimationState::BOMB_EXPLODING, BombExplosionAnimation>(contentManager) && retval;

  setPosition(sf::Vector2f(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f));
  deactivate();
  return retval;
}

void Bomb::activate()
{
  Publisher::addSubscriber(*this, EXPLOSION);
  currentState = AnimationState::BOMB_IDLE;
  AnimatedGameObject::activate();
}

void Bomb::deactivate()
{
   Publisher::removeSubscriber(*this, EXPLOSION);
  currentState = AnimationState::NB_STATES;  
  AnimatedGameObject::deactivate();
  
}

void Bomb::trigger()
{
  if (currentState != AnimationState::BOMB_EXPLODING)
  {
    currentState = AnimationState::BOMB_EXPLODING;
    totalTimeExploding = 0;
  }

}

bool Bomb::update(float deltaT, const Inputs& inputs)
{
  if (!isActive())
    return false;
  bool retval = AnimatedGameObject::update(deltaT, inputs);
  totalTimeExploding += deltaT;
  if (currentState == AnimationState::BOMB_EXPLODING)
  {
    if (totalTimeExploding >= BombExplosionAnimation::ANIMATION_LENGTH)
    {
      deactivate();
      Publisher::notifySubscribers(EXPLOSION, this); 
    }
  }
  return retval;
}

void Bomb::notify(Event event, const void* data)
{
    if (data != this) {
        Bomb* bomb = (Bomb*)data;
        sf::Vector2f pos = bomb->getPosition();
        float xDist = abs(getPosition().x - pos.x);
        float yDist = abs(getPosition().y - pos.y);
        float dist = sqrt(powf(xDist, 2) + powf(yDist, 2));
        int damage = std::max(Bomb::BOMB_RANGE - (int)dist, 0) / 5;
        if (damage >= 100)
            trigger();
    }
}



