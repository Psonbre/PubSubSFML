#include "stdafx.h"
#include "BombExplosionAnimation.h"
#include "Level01ContentManager.h"

const float BombExplosionAnimation::ANIMATION_LENGTH = 2.5f;
const unsigned int BombExplosionAnimation::ANIMATION_LENGTH_IN_FRAMES = 13;

BombExplosionAnimation::BombExplosionAnimation(sf::Sprite& s)
  : LinearAnimation(s, ANIMATION_LENGTH)
{

}


bool BombExplosionAnimation::init(const ContentManager& manager)
{
  const Level01ContentManager& contentManager = dynamic_cast<const Level01ContentManager&>(manager);
  const sf::Texture& texture = contentManager.getBombExplosionTexture();
  sf::IntRect rect(0, 0, texture.getSize().x / 13, texture.getSize().y);
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  rect.left += texture.getSize().x / 13;
  frames.push_back(AnimationFrame(contentManager.getBombExplosionTexture(), rect));
  return true;
}