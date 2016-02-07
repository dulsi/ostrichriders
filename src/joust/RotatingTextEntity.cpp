/**  This file is part of sfmlGame.
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

#include "RotatingTextEntity.h"

RotatingTextEntity::RotatingTextEntity(const sf::Font* font, int size, float x, float y) : TextEntity(font, size, x, y), current(0), currentTime(0.0)
{
}

void RotatingTextEntity::render(sf::RenderWindow* app)
{
    string->setString(texts[current]);
    TextEntity::render(app);
}

void RotatingTextEntity::animate(float delay)
{
    if (texts.size() > 1)
    {
        currentTime += delay;
        if (currentTime >= ROTATING_DELAY)
        {
            current = ++current % texts.size();
            currentTime = currentTime - (((int)currentTime / ROTATING_DELAY) * ROTATING_DELAY);
        }
    }
    GameEntity::animate(delay);
}

void RotatingTextEntity::setText(size_t index, std::string text)
{
    while (index >= texts.size())
        texts.push_back("");
    texts[index] = text;
}

void RotatingTextEntity::setText(size_t index, int intText)
{
    while (index >= texts.size())
        texts.push_back("");
    std::ostringstream intStream;
    intStream << intText;
    texts[index] = intStream.str();
}
