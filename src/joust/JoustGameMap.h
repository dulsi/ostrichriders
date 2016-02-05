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

#ifndef JOUSTGAMEMAP_H_INCLUDED
#define JOUSTGAMEMAP_H_INCLUDED

#include "../sfmlGame/Model/GameMap.h"
#include "../sfmlGame/MyTools.h"
#include "Constants.h"
#include <vector>
#include <cstdlib>
#include <fstream>

const int TILE_EMPTY = 0;

const int GROUND_PLATEFORM_MIN = 3;
const int GROUND_PLATEFORM_MAX = 9;

const int PLATEFORM_MIN = 3;
const int PLATEFORM_MAX = 9;

const int NB_PLATEFORMS = 7;

//const int TILE_GATE = 2;
//const int TILE_LAVA = 3;

class JoustGameMap : public GameMap
{
public:
    JoustGameMap(int width, int height);
    virtual ~JoustGameMap();

    std::vector<IntCoord> getGates();
    int getDifferenceTile(int x, int y);
    int getBotToCome(int n);

    void initDifferenceMap();

    void loadFromFile(const char* fileName, bool firsLevel);
    void searchGates();
    void nextRandomMap(int level);
    void generateRandomLevel();
    void generateRandomMap();
    bool fillRandomMap();
    void generateRandomEnnemies(int level);

    virtual bool isDownBlocking(int x, int y);
    virtual bool isUpBlocking(int x, int y);
    virtual bool isLeftBlocking(int x, int y);
    virtual bool isRightBlocking(int x, int y);
    bool isLava(int x, int y);
    bool isPortal(int x, int y);
    bool isEmpty(int x, int y);

protected:
    std::vector<IntCoord> gates;
    int differenceMap[MAP_WIDTH][MAP_HEIGHT];
    int botsToCome[N_BOTS];

    struct plateformStruct
    {
        int x;
        int y;
        int size;
        int arg;
    } plateform[NB_PLATEFORMS + 1];
    int tileA, tileB;

    int plateformIndex;
};

#endif // JOUSTGAMEMAP_H_INCLUDED
