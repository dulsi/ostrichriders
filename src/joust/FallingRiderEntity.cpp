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

#include "FallingRiderEntity.h"
#include "Constants.h"

FallingRiderEntity::FallingRiderEntity(sf::Texture* image, float x, float y)
                        : SpriteEntity(image, x, y, JOUSTER_WIDTH, JOUSTER_HEIGHT)
{
    lifetime = REBORN_DELAY / 4;
}

FallingRiderEntity::~FallingRiderEntity()
{
}


void FallingRiderEntity::render(sf::RenderWindow* app)
{
    if ((int)velocity.x < 0)
    {
        sprite.setScale(-1, 1);
    }
    if ((int)velocity.x > 0)
    {
        sprite.setScale(1, 1);
    }

    sprite.setTextureRect(sf::IntRect(0, height, width, height));
    sprite.setPosition(x, y);
    sprite.setRotation(angle);
    sprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)(getFade() * 255)));
    app->draw(sprite);
}

void FallingRiderEntity::setMirror(bool mirror)
{
    if (mirror)
    {
        sprite.setScale(-1, 1);
        setSpin(-50);
    }
    else
    {
        setSpin(50);
    }
}
