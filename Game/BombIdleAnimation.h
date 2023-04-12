#pragma once
#include "LinearAnimation.h"
class BombIdleAnimation :
    public LinearAnimation
{
  static const float ANIMATION_LENGTH;
public:
  BombIdleAnimation(sf::Sprite& s);
  virtual bool init(const ContentManager& contentManager) override;

};

