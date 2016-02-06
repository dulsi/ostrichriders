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

#include <iostream>
#include "Constants.h"
#include "JoustTileMapEntity.h"
#include "JoustGameMap.h"
#include "../sfmlGame/MediaManagers/ImageManager.h"
#include "../sfmlGame/Entity/SpriteEntity.h"

JoustTileMapEntity::JoustTileMapEntity(sf::Texture* image, GameMap* gameMap, int tileWidth, int tileHeight, int tilesProLine)
        : TileMapEntity(image, gameMap, tileWidth, tileHeight, tilesProLine)
{
    backgroundSprite.setTexture(*ImageManager::getImageManager()->getImage(IMAGE_BACKGROUND));
}

JoustTileMapEntity::~JoustTileMapEntity()
{
}

void JoustTileMapEntity::render(sf::RenderWindow* app)
{
    sf::Sprite tileSprite;
    tileSprite.setTexture(*image);

    app->draw(backgroundSprite);

    for (int i = 0; i < gameMap->getWidth(); i++)
        for (int j = 0; j < gameMap->getHeight(); j++)
        {
            tileSprite.setPosition(x + (float)(i * tileWidth), y + (float)(j * tileHeight));
            int nx = gameMap->getTile(i, j) % tilesProLine;
            int ny = gameMap->getTile(i, j) / tilesProLine;

            if (((JoustGameMap*)gameMap)->isLava(i, j))
            {
                int decal = (int)(age * 4.0f) % (TILE_FIRE_OUT - TILE_FIRE_IN + 1);
                nx += decal;
                if (nx > TILE_FIRE_OUT) nx -= TILE_FIRE_OUT - TILE_FIRE_IN + 1;
            }

            tileSprite.setTextureRect(sf::IntRect( nx * tileWidth, ny * tileHeight,
                                                tileWidth, tileHeight));

            app->draw(tileSprite);
        }
}

void JoustTileMapEntity::generateFallingTiles()
{
    for (int i = 0; i < gameMap->getWidth(); i++)
        for (int j = 0; j < gameMap->getHeight(); j++)
        {
            int tile = ((JoustGameMap*)gameMap)->getDifferenceTile(i, j);
            if (tile != 0)
            {
                SpriteEntity* fallingBlock  = new SpriteEntity( image,
                                                                (float)(OFFSET_X + tileWidth * i + tileWidth / 2),
                                                                (float)(OFFSET_Y + tileHeight * j + tileHeight / 2),
                                                                tileWidth,
                                                                tileHeight,
                                                                tilesProLine);
                fallingBlock->setFrame(tile);
                fallingBlock->setLifetime(1.0f);
                fallingBlock->setFading(true);
                fallingBlock->setWeight(30.0f);
                fallingBlock->setSpin(-50.0f + 100.0f * (float)rand() / (float)RAND_MAX);
            }
        }

    ((JoustGameMap*)gameMap)->initDifferenceMap();
}
