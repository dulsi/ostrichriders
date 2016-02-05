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

#ifndef JOUSTTILEMAPENTITY_H_INCLUDED
#define JOUSTTILEMAPENTITY_H_INCLUDED

#include "../sfmlGame/Entity/TileMapEntity.h"

// Basis class for Jouster
class JoustTileMapEntity : public TileMapEntity
{
public:
    JoustTileMapEntity(sf::Image* image, GameMap* gameMap, int tileWidth, int tileHeight, int tilesProLine);
    ~JoustTileMapEntity();

    virtual void render(sf::RenderWindow* app);

    void generateFallingTiles();
private:
    sf::Sprite backgroundSprite;
};

#endif // JOUSTTILEMAPENTITY_H_INCLUDED
