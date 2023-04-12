#pragma once
#include "Scene.h"
class MainMenu :
    public Scene
{
public:
  // Héritées via Scene
  MainMenu();
  ~MainMenu();
  virtual SceneType update() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;
private:
  sf::Text text;
  SceneType nextScene;
};

