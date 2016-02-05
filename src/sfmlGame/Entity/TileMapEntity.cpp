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

#include "TileMapEntity.h"

TileMapEntity::TileMapEntity(sf::Image* image, GameMap* gameMap, int tileWidth, int tileHeight, int tilesProLine)
    : GameEntity(0.0f, 0.0f)
{
    this->image = image;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->tilesProLine = tilesProLine;
    this->gameMap = gameMap;
}

TileMapEntity::~TileMapEntity()
{
}

int TileMapEntity::getTilesProLine()
{
    return tilesProLine;
}

void TileMapEntity::render(sf::RenderWindow* app)
{
    sf::Sprite tileSprite;
    tileSprite.SetImage(*image);

    for (int i = 0; i < gameMap->getWidth(); i++)
        for (int j = 0; j < gameMap->getHeight(); j++)
        {
            tileSprite.SetX(x + (float)(i * tileWidth));
            tileSprite.SetY(y + (float)(j * tileHeight));
            int nx = gameMap->getTile(i, j) % tilesProLine;
            int ny = gameMap->getTile(i, j) / tilesProLine;


            tileSprite.SetSubRect(sf::IntRect( nx * tileWidth, ny * tileHeight,
                                                (nx + 1) * tileWidth, (ny + 1) * tileHeight));

            app->Draw(tileSprite);
        }
}

void TileMapEntity::animate(float delay)
{
    age += delay;
}
