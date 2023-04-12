#pragma once
#include "LinearAnimation.h"
class BombExplosionAnimation :
    public LinearAnimation
{
public:
  static const float ANIMATION_LENGTH;
  static const unsigned int ANIMATION_LENGTH_IN_FRAMES;
public:
  BombExplosionAnimation(sf::Sprite& s);
  virtual bool init(const ContentManager& contentManager) override ;
};

