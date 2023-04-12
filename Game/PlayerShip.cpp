#include "stdafx.h"
#include "PlayerShip.h"
#include <cmath>
#include "game.h"
#include "Level01ContentManager.h"
#include "Bomb.h"
#include "Radiation.h"
#include "Subscriber.h"
#include <iostream>
#include <algorithm>
#include "Publisher.h"
#include "Bomb.h"
const float PlayerShip::MAX_SPEED = 15.0f;

PlayerShip::PlayerShip()
  : GameObject(),
    Subscriber()
  , lifePoints(10000)
{
  vectorialThrust.x = vectorialThrust.y = 0.0f;
  activate();
}
bool PlayerShip::init(const ContentManager& contentManager)
{
  bool retval = GameObject::init(contentManager);
  text.setFont(((const Level01ContentManager&)contentManager).getFont());
  text.setCharacterSize(16);
  text.setFillColor(sf::Color::White);

  return retval;
}
void PlayerShip::draw(sf::RenderWindow& window) const
{
  GameObject::draw(window);
  window.draw(text);
}
const sf::Vector2f& PlayerShip::getVectorialThrust() const
{
  return vectorialThrust;
}

void PlayerShip::notify(Event event, const void* data) {
    switch (event)
    {
         
        case RADIATION: {
            Radiation* rad = (Radiation*)data;
            if (rad->getColor() == this->getColor())
                lifePoints += rad->getForce();
            else
                lifePoints -= rad->getForce();
            break;
        }

        case EXPLOSION: {
            Bomb* bomb = (Bomb*)data;
            sf::Vector2f pos = bomb->getPosition();
            float xDist = abs(getPosition().x - pos.x);
            float yDist = abs(getPosition().y - pos.y);
            float dist = sqrt(powf(xDist, 2) + powf(yDist, 2));
            lifePoints -= std::max(Bomb::BOMB_RANGE - (int)dist, 0)/5;
            break;
        }

        default:
            break;
    }
}


bool PlayerShip::update(float elapsedTime, float thrustValue, float rotationValue)
{

  shipThrust = fabs(thrustValue);

  //Rotation du vaisseau
  rotateInRadians(rotationValue);

  //Angle 0 est un vecteur qui pointe vers la droite, et on augmente l'angle dans le sens des aiguilles d'une montre
  vectorialThrust += sf::Vector2f(cos(getRotationAngleInRadians()), sin(getRotationAngleInRadians())) * shipThrust;

  //On ajoute la poussee à la position
  move(vectorialThrust);

  //Dans bien des vieux jeux la vitesse maximum semble être par axe, mais comme on a de la puissance de calcul
  //on va la faire sur le déplacement total, peu importe l'angle.
  setMaximumThrust();

  //Déplacement potentil de l'autre côté.  On se donne un buffer de la taille de notre objet
  handleOutOfBoundsPosition();

  text.setString(std::to_string(lifePoints));
  text.setPosition(getPosition());


  return false;
}

void PlayerShip::activate()
{
    Publisher::addSubscriber(*this, RADIATION);
    Publisher::addSubscriber(*this, EXPLOSION);
    GameObject::activate();
}

void PlayerShip::deactivate()
{
    Publisher::removeSubscriber(*this, RADIATION);
    Publisher::removeSubscriber(*this, EXPLOSION);
    GameObject::deactivate();
}

void PlayerShip::handleOutOfBoundsPosition()
{
  sf::Vector2f newPosition = getPosition();
  if (newPosition.x > Game::GAME_WIDTH + getGlobalBounds().width / 2.0f)
  {
    newPosition.x -= Game::GAME_WIDTH + getGlobalBounds().width;
  }
  else if (newPosition.x < -getGlobalBounds().width * 0.5f)
  {
    newPosition.x += Game::GAME_WIDTH + getGlobalBounds().width;
  }

  if (newPosition.y > Game::GAME_HEIGHT + getGlobalBounds().height / 2.0f)
  {
    newPosition.y -= Game::GAME_HEIGHT + getGlobalBounds().height;
  }
  else if (newPosition.y < -getGlobalBounds().height * 0.5f)
  {
    newPosition.y += Game::GAME_HEIGHT + getGlobalBounds().height;
  }

  GameObject::setPosition(newPosition);
}



void PlayerShip::setMaximumThrust()
{
  //Calcul de la vitesse maximum actuelle (pythagore)
  float vitesseTotale = sqrt(vectorialThrust.x * vectorialThrust.x + vectorialThrust.y * vectorialThrust.y);

  //Si plus grande que la vitesse actuelle, on se fait un ratio
  if (vitesseTotale > MAX_SPEED)
  {
    vectorialThrust *= MAX_SPEED / vitesseTotale;
  }
}

