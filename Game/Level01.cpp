#include "stdafx.h"
#include "Level01.h"
#include "game.h"
#include "Level01ContentManager.h"
#include "ActorType.h"

const float Level01::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const float Level01::GAMEPAD_SPEEDRATIO = 1000.0f;
const float Level01::KEYBOARD_SPEED = 0.1f;
const float Level01::KEYBOARD_ROTATION = 0.1f;


Level01::Level01()
  : Scene(SceneType::LEVEL01)
  , currentSelectedActor(ActorType::NONE)
{
}

Level01::~Level01()
{

}

SceneType Level01::update()
{
  SceneType retval = getSceneType();
  if (inputs.activeShipMask != -1)
    activeShip = inputs.activeShipMask;


  Inputs& inputs = this->inputs;
  int& activeShip = this->activeShip;
  PlayerShip* ships = this->ships;

  std::for_each(ships, ships + NB_SHIPS, [&inputs, &activeShip, &ships](PlayerShip& p) {p.update(TIME_PER_FRAME, &p == &(ships[activeShip]) ? inputs.thrustMask : 0, &p == &(ships[activeShip]) ? inputs.rotateMask : 0); });

  for (int i = 0; i < NB_MAX_BOMBS; i++)
  {
    bombs[i].update(TIME_PER_FRAME, inputs);
  }
  for (int i = 0; i < NB_MAX_RADIATIONS; i++)
  {
    radiations[i].update(TIME_PER_FRAME);
  }

  manageActorsAdditionAndTriggering();

  return retval;
}

void Level01::pause()
{
  spaceGameMusic.pause();
}

void Level01::unPause()
{
  spaceGameMusic.play();
}

void Level01::draw(sf::RenderWindow& window) const
{
  window.draw(background);
  std::for_each(ships, ships + NB_SHIPS, [&window](PlayerShip p) {p.draw(window); });

  for (int i = 0; i < NB_MAX_BOMBS; i++)
  {
    bombs[i].draw(window);
  }
  for (int i = 0; i < NB_MAX_RADIATIONS; i++)
  {
    radiations[i].draw(window);
  }
}

bool Level01::uninit()
{
  return true;
}

bool Level01::init()
{
  if (false == contentManager.loadContent())
    return false;
  result.level01Result.score = 0;
  inputs.reset();
  activeShip = 0;
  currentSelectedActor = ActorType::BLUE_RADIATION;
  if (!spaceGameMusic.openFromFile("Assets\\Music\\sgMusic.ogg"))
    return false;
  spaceGameMusic.setLoop(true);
  spaceGameMusic.play();

  sf::Color colors[NB_SHIPS] = { sf::Color::Blue, sf::Color::Green, sf::Color::Red };

  ships[0].initialize(contentManager.getPlayerShipTexture(), sf::Vector2f(Game::GAME_WIDTH / 4.0f, Game::GAME_HEIGHT * 0.5f));
  ships[1].initialize(contentManager.getPlayerShipTexture(), sf::Vector2f(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT * 0.5f));
  ships[2].initialize(contentManager.getPlayerShipTexture(), sf::Vector2f(3.0f * Game::GAME_WIDTH / 4.0f, Game::GAME_HEIGHT * 0.5f));
  for (int i = 0; i < NB_SHIPS; i++)
  {
    ships[i].init(contentManager);
    ships[i].setColor(colors[i]);
  }
  for (int i = 0; i < NB_MAX_BOMBS; i++)
  {
    bombs[i].init(contentManager);
  }
  for (int i = 0; i < NB_MAX_RADIATIONS; i++)
  {
    radiations[i].init(contentManager);
  }

  background.setTexture(contentManager.getBackgroundTexture());

  return true;
}

bool Level01::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;
  inputs.reset();
  while (window.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == sf::Event::Closed)
    {
      window.close();
      retval = true;
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
        inputs.leftClick = window.mapPixelToCoords(sf::Mouse::getPosition(window));

      if (event.mouseButton.button == sf::Mouse::Right)
        inputs.rightClick = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }
    if (event.type == sf::Event::KeyPressed)
    {
      //choix des bonus
      if (event.key.code == sf::Keyboard::Z)
        inputs.choiceOfActorMask = ActorType::BLUE_RADIATION;
      else if (event.key.code == sf::Keyboard::X)
        inputs.choiceOfActorMask = ActorType::GREEN_RADIATION;
      else if (event.key.code == sf::Keyboard::C)
        inputs.choiceOfActorMask = ActorType::RED_RADIATION;
      //else if (event.key.code == sf::Keyboard::V)
      //  inputs.choiceOfActorMask = ActorType::HEAL;
      else if (event.key.code == sf::Keyboard::B)
        inputs.choiceOfActorMask = ActorType::BOMB;
    }
  }

  if (false == retval)
  {
    //Si le Gamepad est connecté, on l'utilise pour sélectionner et déplacer les vaisseaux
    if (sf::Joystick::isConnected(0))
    {
      inputs.thrustMask = -Inputs::eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)) / GAMEPAD_SPEEDRATIO;
      inputs.rotateMask = Inputs::eliminateVibration(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / GAMEPAD_SPEEDRATIO;
      if (sf::Joystick::isButtonPressed(0, 2))
        inputs.activeShipMask = 0;
      if (sf::Joystick::isButtonPressed(0, 0))
        inputs.activeShipMask = 1;
      if (sf::Joystick::isButtonPressed(0, 1))
        inputs.activeShipMask = 2;
    }
    //Sinon on se rabat sur le clavier
    else
    {
      inputs.rotateMask = 0.0f;
      inputs.thrustMask = 0.0f;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        inputs.activeShipMask = 0;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        inputs.activeShipMask = 1;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        inputs.activeShipMask = 2;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        inputs.rotateMask -= KEYBOARD_ROTATION;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        inputs.rotateMask += KEYBOARD_ROTATION;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        inputs.thrustMask = KEYBOARD_SPEED;
    }
  }
  return retval;
}

Bomb& Level01::getNextAvailableBomb()
{
  for (int i = 0; i < NB_MAX_BOMBS; i++)
  {
    if (!bombs[i].isActive())
    {
      bombs[i].activate();
      return bombs[i];
    }
  }
  return bombs[0];
}

Radiation& Level01::getNextAvailableRadiation()
{
  for (int i = 0; i < NB_MAX_BOMBS; i++)
  {
    if (!radiations[i].isActive())
    {
      radiations[i].activate();
      return radiations[i];
    }
  }
  return radiations[0];
}

void Level01::manageActorsAdditionAndTriggering()
{
  if (inputs.choiceOfActorMask != ActorType::NONE)
    currentSelectedActor = inputs.choiceOfActorMask;

  if (inputs.leftClick.x != -1)
  {

    if (currentSelectedActor == ActorType::BOMB)
    {
      Bomb& bomb = getNextAvailableBomb();
      bomb.setPosition(inputs.leftClick);
    }
    else
    {
      Radiation& radiation = getNextAvailableRadiation();
      switch (currentSelectedActor)
      {
      case ActorType::BLUE_RADIATION:
      {
        radiation.setColor(sf::Color::Blue);
        break;
      }
      case ActorType::GREEN_RADIATION:
      {
        radiation.setColor(sf::Color::Green);
        break;
      }
      case ActorType::RED_RADIATION:
      {
        radiation.setColor(sf::Color::Red);
        break;
      }
      }
      radiation.setPosition(inputs.leftClick);
      radiation.activate();

    }

  }
  if (inputs.rightClick.x != -1)
  {
    activateBombAtClick();
    activateRadiationAtClick();
  }
}

void Level01::activateBombAtClick()
{
  for (int i = 0; i < NB_MAX_BOMBS; i++)
  {
    if (bombs[i].collidesWith(inputs.rightClick))
    {
      bombs[i].trigger();
    }
  }
}


void Level01::activateRadiationAtClick()
{
  for (int i = 0; i < NB_MAX_RADIATIONS; i++)
  {
    if (radiations[i].collidesWith(inputs.rightClick))
    {
      radiations[i].trigger();
    }
  }
}