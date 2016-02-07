/**  This file is part of Ostrich Riders.
  *
  *  FreeTumble is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  FreeTumble is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with FreeTumble.  If not, see <http://www.gnu.org/licenses/>.
  */

#include <sstream>
#include <iostream>

#include "LifeEntity.h"
#include "Constants.h"

LifeEntity::LifeEntity(sf::Texture *image, float x, float y, int *lives)
                                    : SpriteEntity(image, x, y, LIFE_WIDTH, LIFE_HEIGHT), current(0), currentTime(0.0)
{
    this->lives.push_back(lives);
}

void LifeEntity::addLives(sf::Texture *image, int *lives)
{
    this->lives.push_back(lives);
    sprites.push_back(sf::Sprite());
    sprites.back().setTexture(*image);
    sprites.back().setOrigin((float)(this->width / 2), (float)(this->height / 2));
}

void LifeEntity::animate(float delay)
{
    if (lives.size() > 1)
    {
        currentTime += delay;
        if (currentTime >= ROTATING_DELAY)
        {
            current = ++current % lives.size();
            currentTime = currentTime - (((int)currentTime / ROTATING_DELAY) * ROTATING_DELAY);
        }
    }
    SpriteEntity::animate(delay);
}

void LifeEntity::render(sf::RenderWindow* app)
{
    if (*(lives[current]) < 1) return;
    sf::Sprite *currentSprite = &sprite;
    if (current > 0)
        currentSprite = &sprites[current - 1];

    int lives_to_show = *(lives[current]);
    if (lives_to_show > 4) lives_to_show = 3;

    for (int i = 0; i < lives_to_show; i++)
    {
        currentSprite->setPosition(x + (float)(i * 21), y);
        app->draw(*currentSprite);
    }

    if (*(lives[current]) > 4)
    {
        int lives_to_write = *(lives[current]) - 3;

        std::ostringstream intStream;
        intStream << "+" << lives_to_write;

        sf::Text string;

        string.setString(intStream.str());
        string.setCharacterSize(17);
        string.setColor(sf::Color(128, 128, 255, 255));

        string.setPosition(x + 3 * 20 - 4, y - string.getGlobalBounds().height / 2 - 2);

        app->draw(string);
    }
}
