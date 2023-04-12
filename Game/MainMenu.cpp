#include "stdafx.h"
#include "MainMenu.h"
#include "ContentManager.h"
#include "game.h"

MainMenu::MainMenu()
  : Scene(SceneType::MAIN_MENU)
  , nextScene(SceneType::MAIN_MENU)
{

}

MainMenu::~MainMenu()

{

}
SceneType MainMenu::update()
{
  if (nextScene != SceneType::MAIN_MENU)
  {
    SceneType retval = nextScene;
    nextScene = SceneType::MAIN_MENU;
    return retval;
  }
  return nextScene = getSceneType();
}

void MainMenu::draw(sf::RenderWindow& window) const
{
  window.draw(text);
}

bool MainMenu::init()
{

  bool retval = true;
  text.setFont(ContentManager::getInstance().GetMainMenuFont());
  text.setString("MainMenu\nPress enter to start game\nPress q to quit");
  text.setPosition((Game::GAME_WIDTH - text.getLocalBounds().width) / 2, (Game::GAME_HEIGHT - text.getLocalBounds().height) / 2);
  return retval;
}

bool MainMenu::uninit()
{
  return false;
}

bool MainMenu::handleEvents(sf::RenderWindow& window)
{
  bool windowIsClosed = Scene::handleEvents(window);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    nextScene = SceneType::LEVEL01;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    nextScene = SceneType::NONE;
  return windowIsClosed;
}