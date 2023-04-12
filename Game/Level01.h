#pragma once
#include "Scene.h"
#include "Inputs.h"
#include "PlayerShip.h"
#include "Level01ContentManager.h"
#include "Bomb.h"
#include "Radiation.h"

#define NB_SHIPS 3
#define NB_MAX_BOMBS 20
#define NB_MAX_RADIATIONS 20
class Level01 :
  public Scene
{
public:
  static const float TIME_PER_FRAME;
  static const float GAMEPAD_SPEEDRATIO;
  static const float KEYBOARD_SPEED;
  static const float KEYBOARD_ROTATION;

public:
  // Héritées via Scene
  Level01();
  ~Level01(); 
  virtual SceneType update() override;
  virtual void pause()override;
  virtual void unPause() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;
private:
  void manageActorsAdditionAndTriggering();
  void activateBombAtClick();
  void activateRadiationAtClick();
  Inputs inputs;
  PlayerShip ships[NB_SHIPS];
  sf::Sprite background;
  sf::Music spaceGameMusic;
  Level01ContentManager contentManager;
  int activeShip;
  ActorType currentSelectedActor;
  
  Bomb bombs[NB_MAX_BOMBS];
  Bomb& getNextAvailableBomb();
  Radiation radiations[NB_MAX_RADIATIONS];
  Radiation& getNextAvailableRadiation();
};

