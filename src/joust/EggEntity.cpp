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

#include "EggEntity.h"
#include "LogicEngine.h"
#include "Constants.h"
#include "GameConstants.h"
#include "../sfmlGame/MediaManagers/ImageManager.h"

EggEntity::EggEntity(sf::Image* image, float x, float y)
                                    : CollidingSpriteEntity(image, x, y, EGG_WIDTH, EGG_HEIGHT)
{
    weight =        GameConstants::getGameConstants()->JOUSTER_WEIGHT;
    normalWeight =  weight;
    eggType = 0;

    incubationDelay = EGG_INCUBATION_DELAY_MIN + (float)rand() / (float)RAND_MAX
                            * (EGG_INCUBATION_DELAY_MAX - EGG_INCUBATION_DELAY_MIN);

}

EggEntity::~EggEntity()
{
}

void EggEntity::render(sf::RenderWindow* app)
{
    // rendering the rider
    sprite.SetSubRect(sf::IntRect(0, height, width, 2 * height));
    sprite.SetX(x);
    sprite.SetY(y);
    app->Draw(sprite);

    CollidingSpriteEntity::render(app);
}

int EggEntity::getEggType() { return eggType; }
void EggEntity::setEggType(int eggType) { this->eggType = eggType; }
void EggEntity::animate(float delay)
{
    velocity.x *= EGG_VISCOSITY;
    velocity.y *= EGG_VISCOSITY;
    CollidingSpriteEntity::animate(delay);

    if (age > incubationDelay)
    {
        LogicEngine::getLogicEngine()->onIncubate(this);
        return;
    }
    else if (age > incubationDelay - 6.0f)
    {
        float xScale = 1.1f + 0.3f * cosf(age * 5);
        float yScale = 1.1f + 0.3f * sinf(age * 5);
        sprite.SetScale(xScale, yScale);
    }

    if (collidingWithLava())
    {
        isDying = true;
        LogicEngine::getLogicEngine()->onEggInLava();

        for (int i = 0; i < 7; i++)
        {
            SpriteEntity* part = new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_BLACK_PART), x, y);
            part->setLifetime(1.0f);
            part->setFading(true);
            part->setVelocity(Vector2D(-20.0f + (float)rand() / (float)RAND_MAX * 40.0f,
                                            -20.0f + (float)rand() / (float)RAND_MAX * 40.0f));
            part->setWeight(-40.0f);
        }
    }
}

void EggEntity::exitMap(int direction)
{
    switch (direction)
    {
    case DIRECTION_LEFT:
        x = (float)(map->getWidth() * (tileWidth - 1) + width / 2 + offsetX);
        break;

    case DIRECTION_RIGHT:
        x = (float)(1 - width / 2 + offsetX);
        break;
    }
}

bool EggEntity::collidingWithLava()
{
    if (boundingBox.Bottom > (tileHeight - 2) * map->getHeight() + TILE_HEIGHT) return true;
    return false;
}
