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

#include "BurningJousterEntity.h"
#include "Constants.h"

BurningJousterEntity::BurningJousterEntity(sf::Texture* image, float x, float y)
                        : SpriteEntity(image, x, y, JOUSTER_WIDTH, JOUSTER_HEIGHT)
{
    lifetime = 3 * REBORN_DELAY / 4;
}

BurningJousterEntity::~BurningJousterEntity()
{
}

void BurningJousterEntity::render(sf::RenderWindow* app)
{
    if ((int)velocity.x < 0)
    {
        sprite.setScale(-1, 1);
    }
    if ((int)velocity.x > 0)
    {
        sprite.setScale(1, 1);
    }

    int y0 = (int)y - 2 +  (int)((float)height * (1.0f - getFade()));
    int yf = height - (int)((float)height * getFade());

    sprite.setTextureRect(sf::IntRect(0, 0, width, height - yf));
    sprite.setPosition(x, (float)y0);

    sprite.setColor(sf::Color((sf::Uint8)(getFade() * 255),
                        (sf::Uint8)(getFade() * 64),
                        (sf::Uint8)(getFade() * 64),
                        255));
    app->draw(sprite);

    sprite.setTextureRect(sf::IntRect(0, height, width, (2 * height - yf) - height));
    app->draw(sprite);
}

void BurningJousterEntity::setMirror(bool mirror)
{
    if (mirror)
    {
        sprite.setScale(-1, 1);
    }
}
