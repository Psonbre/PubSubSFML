#pragma once
#include "Scene.h"
class PauseMenu : public Scene
{
public:
  // Héritées via Scene
  PauseMenu();
  ~PauseMenu();
  virtual SceneType update() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;
private:
  sf::Text text;
  bool shouldEnd;
};

