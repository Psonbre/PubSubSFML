#pragma once
#include "AnimatedGameObject.h"
#include "Subscriber.h"

class Bomb :
    public AnimatedGameObject,
    public Subscriber
{
public:

  static const int BOMB_RANGE;
  virtual bool init(const ContentManager& contentManager) override;
  void trigger();
  virtual void activate()override;
  virtual void deactivate() override;
  virtual bool update(float deltaT, const Inputs& inputs) override;
  void notify(Event event, const void* data) override;
  private:
  float totalTimeExploding;
};

