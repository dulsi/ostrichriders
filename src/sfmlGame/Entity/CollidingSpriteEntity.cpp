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

#include "CollidingSpriteEntity.h"

CollidingSpriteEntity::CollidingSpriteEntity(sf::Texture* image, float x, float y, int width, int height)
                                                    : SpriteEntity(image, x, y, width, height)
{
    maxY = 1000.0f;
}

CollidingSpriteEntity::~CollidingSpriteEntity()
{
}

GameMap* CollidingSpriteEntity::getMap()
{
    return map;
}

void CollidingSpriteEntity::setMap(GameMap* map, int tileWidth, int tileHeight, int offsetX, int offsetY)
{
    this->map = map;
    setTileDimensions(tileWidth, tileHeight);
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

void CollidingSpriteEntity::setTileDimensions(int width, int height)
{
    tileWidth = width;
    tileHeight = height;
}

void CollidingSpriteEntity::render(sf::RenderWindow* app)
{
    SpriteEntity::render(app);
}


void CollidingSpriteEntity::animate(float delay)
{
    if ((int)velocity.x > 0)
    {
        x += velocity.x * delay;

        if (collideWithMap(DIRECTION_LEFT))
        {
            collideMapRight();
            //x = (float)((int)x);
            while (collideWithMap(DIRECTION_LEFT))
            {
                x--;
            }
        }
        else if (x > map->getWidth() * tileWidth + offsetX)
        {
            exitMap(DIRECTION_RIGHT);
        }
    }
    else if ((int)velocity.x < 0)
    {
        x += velocity.x * delay;

        if (collideWithMap(DIRECTION_RIGHT))
        {
            collideMapLeft();
            //x = (float)((int)x);
            while (collideWithMap(DIRECTION_RIGHT))
            {
                x++;
            }
        }
        else if (x < offsetX)
        {
            exitMap(DIRECTION_LEFT);
        }
    }

    velocity.y += weight * delay;
    if ( velocity.y > maxY) velocity.y = maxY;

    if ((int)velocity.y > 0)
    {
        y += velocity.y * delay;
        //calculateBB();

        if (collideWithMap(DIRECTION_BOTTOM))
        {
            weight = 0;
            velocity.y = 0.0f;

            y = (float)((int)y);
            while (collideWithMap(DIRECTION_BOTTOM))
            {
                y--;
                //calculateBB();
            }
        }
    }
    else if ((int)velocity.y < 0)
    {
        y += velocity.y * delay;
        //calculateBB();

        if (collideWithMap(DIRECTION_TOP))
        {
            velocity.y = -0.5f * velocity.y;

            y = (float)((int)y);
            while (collideWithMap(DIRECTION_TOP))
            {
                y++;
                //calculateBB();
            }
        }
    }




    if ((int)weight == 0)
    {
        if (!(isOnGround()))
        {
            makeFall();
        }
    }

    if (lifetime > 0)
    {
        if (age >= lifetime) isDying = true;
    }
    age += delay;
}

void CollidingSpriteEntity::calculateBB()
{
    boundingBox.left = (int)x - width / 2;
    boundingBox.width = width;
    boundingBox.top = (int)y - height / 2;
    boundingBox.height = height;
}

void CollidingSpriteEntity::makeFall()
{
    weight = normalWeight;
}

bool CollidingSpriteEntity::isOnGround()
{
    calculateBB();

    int xTile0 = (boundingBox.left - offsetX) / tileWidth;
    int xTilef = (boundingBox.left + boundingBox.width - offsetX) / tileWidth;
    int yTile = (boundingBox.top + boundingBox.height + 1 - offsetY) / tileHeight;

    for (int xTile = xTile0; xTile <= xTilef; xTile++)
    {
        if (map->isDownBlocking(xTile, yTile)) return true;
    }
    return false;
}

void CollidingSpriteEntity::exitMap(int direction)
{
    if (direction == 0) {}
}

void CollidingSpriteEntity::collideMapRight()
{
    velocity.x = 0.0f;
}

void CollidingSpriteEntity::collideMapLeft()
{
    velocity.x = 0.0f;
}



bool CollidingSpriteEntity::collideWithMap(int direction)
{
    calculateBB();

    int xTile0 = (boundingBox.left - offsetX) / tileWidth;
    int xTilef = (boundingBox.left + boundingBox.width - offsetX) / tileWidth;
    int yTile0 = (boundingBox.top - offsetY) / tileHeight;
    int yTilef = (boundingBox.top + boundingBox.height - offsetY) / tileHeight;

    if (boundingBox.top < 0) yTile0 = -1;

    for (int xTile = xTile0; xTile <= xTilef; xTile++)
        for (int yTile = yTile0; yTile <= yTilef; yTile++)
        {
            switch (direction)
            {
            case DIRECTION_LEFT:
                if (map->isLeftBlocking(xTile, yTile)) return true;
                break;

            case DIRECTION_RIGHT:
                if (map->isRightBlocking(xTile, yTile)) return true;
                break;

            case DIRECTION_TOP:
                if (map->isUpBlocking(xTile, yTile)) return true;
                break;

            case DIRECTION_BOTTOM:
                if (map->isDownBlocking(xTile, yTile)) return true;
                break;
            }
        }

    return false;
}

bool CollidingSpriteEntity::collideWithEntity(CollidingSpriteEntity* entity)
{
    calculateBB();
    entity->calculateBB();

    if (boundingBox.left > entity->boundingBox.left + entity->boundingBox.width) return false;
    if (boundingBox.left + boundingBox.width < entity->boundingBox.left) return false;
    if (boundingBox.top > entity->boundingBox.top + entity->boundingBox.height) return false;
    if (boundingBox.top + boundingBox.height < entity->boundingBox.top) return false;

    return true;
}

void CollidingSpriteEntity::testSpriteCollisions()
{
    EntityManager::EntityList* entityList = EntityManager::getEntityManager()->getList();

    EntityManager::EntityList::iterator it;
    EntityManager::EntityList::iterator oldit = entityList->begin ();

    for (it = entityList->begin (); it != entityList->end ();)
    {
        GameEntity* entity = *it;

        CollidingSpriteEntity* collidingEntity = dynamic_cast<CollidingSpriteEntity*>(entity);
        if (collidingEntity != NULL)
        {
            readCollidingEntity(collidingEntity);
        }
        oldit = it;
        it++;

    } // end for*/
}

void CollidingSpriteEntity::readCollidingEntity(CollidingSpriteEntity* entity)
{
    if (entity == NULL) return;
}

void CollidingSpriteEntity::collideEntity(CollidingSpriteEntity* entity)
{
    if (entity == NULL) return;
}
