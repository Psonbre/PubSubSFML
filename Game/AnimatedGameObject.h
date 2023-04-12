#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "AnimationState.h"

class ContentManager;
class Animation;
struct Inputs;
class AnimatedGameObject :
  public GameObject
{
public:
  AnimatedGameObject();
  virtual ~AnimatedGameObject();
  AnimatedGameObject(const AnimatedGameObject& src);

  virtual bool update(float deltaT, const Inputs& inputs);
  
  virtual bool init(const ContentManager& contentManager);

protected:
  AnimationState currentState;
  template<AnimationState state, class AnimationType >
  bool addAnimation(const ContentManager& contentManager)
  {
    Animation* animation = new AnimationType(*this);
    bool retval = animation->init(contentManager);
    if (retval)
      animations[state] = animation;
    return retval;
  }
  std::map<AnimationState, Animation*> animations;
  ContentManager* contentManager;
private:
  AnimatedGameObject& operator=(const AnimatedGameObject&);


};

