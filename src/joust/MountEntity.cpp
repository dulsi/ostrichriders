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

#include "MountEntity.h"
#include "Constants.h"

MountEntity::MountEntity(sf::Texture* image, int spriteType, float x, float y)
                        : JousterEntity(image, spriteType, x, y)
{
    lifetime = REBORN_DELAY;
    botJumpDelay = 0.3f + (float)rand() / (float)RAND_MAX * 0.5f;
}

MountEntity::~MountEntity()
{
}

void MountEntity::setLeftDirection(bool isLeftDirection)
{
    this->isLeftDirection = isLeftDirection;
}

void MountEntity::animate(float delay)
{
    botJumpDelay -= delay;
    wannaJump = false;
    if (botJumpDelay <= 0.0f)
    {
        wannaJump = true;
        botJumpDelay = 0.3f + (float)rand() / (float)RAND_MAX * 0.5f;
    }

    wannaGoLeft = false;
    wannaGoRight = false;

    if (isLeftDirection)
    {
        wannaGoLeft = true;
    }
    else
    {
        wannaGoRight = true;
    }


    JousterEntity::animate(delay);
}

void MountEntity::render(sf::RenderWindow* app)
{
    if ((int)velocity.x < 0)
    {
        sprite.setScale(-1, 1);
    }
    if ((int)velocity.x > 0)
    {
        sprite.setScale(1, 1);
    }

    findFrame();

    CollidingSpriteEntity::render(app);
}

void MountEntity::exitMap(int direction)
{
    isDying = true;
    if (direction == 0) {}
}
