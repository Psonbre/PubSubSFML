#include "stdafx.h"
#include "BombIdleAnimation.h"
#include "Level01ContentManager.h"

const float BombIdleAnimation::ANIMATION_LENGTH = 1.0f;

BombIdleAnimation::BombIdleAnimation(sf::Sprite& s)
  : LinearAnimation(s, ANIMATION_LENGTH)
{

}

bool BombIdleAnimation::init(const ContentManager& manager)
{
  const Level01ContentManager& contentManager = dynamic_cast<const Level01ContentManager&>(manager);
  const sf::Texture& texture = contentManager.getBombExplosionTexture();
  sf::IntRect rect(0, 0, texture.getSize().x / 13, texture.getSize().y);
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  
  return true;
}