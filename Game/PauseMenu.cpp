#include "stdafx.h"
#include "PauseMenu.h"

#include "ContentManager.h"

#include "game.h"
PauseMenu::PauseMenu()
  : Scene(SceneType::PAUSE_MENU)
{

}
PauseMenu::~PauseMenu()
{

}
SceneType PauseMenu::update()
{
  SceneType nextScene = getSceneType();
  if (shouldEnd)
  {
    shouldEnd = false;
    nextScene = SceneType::NONE;

  }
  return nextScene;
}

#include <iostream>
void PauseMenu::draw(sf::RenderWindow& window) const
{
std::cout << result.level01Result.score <<std::endl;
  window.draw(text);
}

bool PauseMenu::init()
{
  shouldEnd = false;
  bool retval = true;
  text.setFont(ContentManager::getInstance().GetMainMenuFont());
  text.setString("PauseMenu\nPress backspace to return to game game");
  text.setPosition((Game::GAME_WIDTH - text.getLocalBounds().width) / 2, (Game::GAME_HEIGHT - text.getLocalBounds().height) / 2);
  return retval;
}

bool PauseMenu::uninit()
{
  return false;
}

bool PauseMenu::handleEvents(sf::RenderWindow& window)
{
  bool windowIsClosed = Scene::handleEvents(window);
  shouldEnd = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace);
  return windowIsClosed;
}