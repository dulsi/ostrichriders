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

LifeEntity::LifeEntity(sf::Image* image, float x, float y, int lives)
                                    : SpriteEntity(image, x, y, LIFE_WIDTH, LIFE_HEIGHT)
{
    this->lives = lives;

    //width = JOUSTER_WIDTH;
    //height = JOUSTER_HEIGHT;

    //sprite.SetSubRect(sf::IntRect(0, height, width, 2 * height));
    //sprite.SetScale(0.5f, 0.5f);
}


void LifeEntity::render(sf::RenderWindow* app)
{
    if (lives < 1) return;

    int lives_to_show = lives;
    if (lives > 4) lives_to_show = 3;

    for (int i = 0; i < lives_to_show; i++)
    {
        sprite.SetX(x + (float)(i * 21));
        sprite.SetY(y);
        app->Draw(sprite);
    }

    if (lives > 4)
    {
        int lives_to_write = lives - 3;

        std::ostringstream intStream;
        intStream << "+" << lives_to_write;

        sf::String string;

        string.SetText(intStream.str());
        string.SetSize(17);
        string.SetColor(sf::Color(128, 128, 255, 255));

        string.SetX(x + 3 * 20 - 4);
        string.SetY(y - string.GetRect().GetHeight() / 2 - 2);

        app->Draw(string);
    }
}

void LifeEntity::setLives(int lives) { this->lives = lives; }
