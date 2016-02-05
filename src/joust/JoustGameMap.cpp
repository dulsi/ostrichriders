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
#include "JoustGameMap.h"

JoustGameMap::JoustGameMap(int width, int height) : GameMap(width, height)
{
}

JoustGameMap::~JoustGameMap()
{
}

void JoustGameMap::initDifferenceMap()
{
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++)
            differenceMap[i][j] = 0;
}

void JoustGameMap::loadFromFile(const char* fileName, bool firstLevel)
{
    //ifstream f(fileName);
    static ifstream f;
    f.open(fileName);
    if (!f.is_open())
    {
        printf("[ERROR] Impossible to open file: %s\n", fileName);
        return;
    }

    int n;
    int i;

	// dimensions
	f >> botsToCome[0];
    f >> botsToCome[1];
    f >> botsToCome[2];
    f >> botsToCome[3];


    for (int j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            f >> n;
            if (firstLevel)
            {
                differenceMap[i][j] = 0;
            }
            else
            {
                if (map[i][j] == n)
                {
                    differenceMap[i][j] = 0;
                }
                else
                {
                    differenceMap[i][j] = map[i][j];
                }
            }
            map[i][j] = n;
        }
    }

    f.close();

    searchGates();
}

void JoustGameMap::nextRandomMap(int level)
{
    if (level == 1)
    {
        initDifferenceMap();
        generateRandomLevel();
    }
    else if (level == 3)
    {
        for (int i = 0; i < MAP_WIDTH; i++)
        {
            if (map[i][MAP_HEIGHT - 2] >= 130)
            {
                differenceMap[i][MAP_HEIGHT - 2] = map[i][MAP_HEIGHT - 2];
                map[i][MAP_HEIGHT - 2] = 0;
            }
        }
    }
    else if (level == 4)
    {
    }
    else
    {
        int i;
        if (plateformIndex > 0)
        {
            if (plateform[plateformIndex].arg > 0)
            {
                for (i = plateform[plateformIndex].x - 1; i <= plateform[plateformIndex].x + plateform[plateformIndex].size; i++)
                {
                    int mx = i % MAP_WIDTH;
                    int my = plateform[plateformIndex].y + 1;
                    differenceMap[mx][my] = map[mx][my];
                    map[mx][my] = 0;
                }
                plateform[plateformIndex].arg = 0;
            }
            else
            {
                for (i = plateform[plateformIndex].x; i <= plateform[plateformIndex].x + plateform[plateformIndex].size - 1; i++)
                {
                    int mx = i % MAP_WIDTH;
                    int my = plateform[plateformIndex].y;
                    differenceMap[mx][my] = map[mx][my];
                    map[mx][my] = 0;
                }
                plateformIndex--;
            }
        }
    }
    generateRandomEnnemies(level);
    searchGates();
}

void JoustGameMap::generateRandomLevel()
{
    generateRandomMap();
    while (!fillRandomMap())
    {
        generateRandomMap();
    }

    plateformIndex = NB_PLATEFORMS;
}

void JoustGameMap::generateRandomMap()
{
    int x, y, size;

    tileA = rand() % 20;
    tileB = rand() % 20;

    // ground plateform
    size = GROUND_PLATEFORM_MIN + rand() % (GROUND_PLATEFORM_MAX - GROUND_PLATEFORM_MIN + 1);
    x = 5 + rand() % (MAP_WIDTH - 10 - size);

    plateform[0].x = x;
    plateform[0].size = size;

    for (int i = 1; i <= NB_PLATEFORMS; i++)
    {
        x = 2 + rand() % (MAP_WIDTH - 4);
        y = 2 + rand() % (MAP_HEIGHT - 6);
        size = PLATEFORM_MIN + rand() % (PLATEFORM_MAX - PLATEFORM_MIN + 1);

        plateform[i].x = x;
        plateform[i].y = y;
        plateform[i].size = size;

        if (rand() % 2 == 0)
        {
            plateform[i].arg = 0;
        }
        else
        {
            plateform[i].arg = 1 + rand() % 4;
        }
    }
}

bool JoustGameMap::fillRandomMap()
{
    int i, j, middle;
    for (i = 0; i < MAP_WIDTH; i++)
    {
        for (j = 0; j < MAP_HEIGHT - 1; j++)
        {
            map[i][j] = 0;
        }
        map[i][MAP_HEIGHT - 1] = 1 + i % 6;
    }

    // ground plateform
    for (i = plateform[0].x; i < plateform[0].x + plateform[0].size; i++)
    {
        for (j = MAP_HEIGHT - 2; j < MAP_HEIGHT; j++)
        {
            int r = rand() % 18;
            if (r == 0)
                map[i][j] = 33 + tileA * 5;
            else if (r == 1)
                map[i][j] = 34 + tileA * 5;
            else
                map[i][j] = 30 + tileA * 5;
            }
    }
    middle = plateform[0].x + plateform[0].size / 2;
    if (plateform[0].size % 2 == 0 && rand() % 2 == 0) middle--;
    map[middle][MAP_HEIGHT - 2] = 10 + tileA;

    // bridge
    int bridgeTile = 130 + rand() % 13;
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        if (map[i][MAP_HEIGHT - 2] == 0)
            map[i][MAP_HEIGHT - 2] = bridgeTile;
    }

    // plateforms
    for (int j = 1; j <= NB_PLATEFORMS; j++)
    {
        int tile = rand() % 2 == 0 ? tileA : tileB;
        for (i = plateform[j].x; i < plateform[j].x + plateform[j].size; i++)
        {
            int x = i % MAP_WIDTH;
            if (map[x][plateform[j].y] > 0) return false;
            if (map[(x + 2) % MAP_WIDTH][plateform[j].y] > 0) return false;
            if (map[x][plateform[j].y-1] > 0) return false;
            if (map[x][plateform[j].y-2] > 0) return false;
            if (map[x][plateform[j].y+1] > 0) return false;
            if (map[x][plateform[j].y+2] > 0) return false;

            if (i == plateform[j].x)
            {
                if (map[(x - 2 + MAP_WIDTH) % MAP_WIDTH][plateform[j].y] > 0) return false;
                map[x][plateform[j].y] = 31 + tile * 5;
            }
            else if (i == plateform[j].x + plateform[j].size - 1)
            {
                map[x][plateform[j].y] = 32 + tile * 5;
            }
            else
            {
                int r = rand() % 18;
                if (r == 0)
                    map[x][plateform[j].y] = 33 + tile * 5;
                else if (r == 1)
                    map[x][plateform[j].y] = 34 + tile * 5;
                else
                    map[x][plateform[j].y] = 30 + tile * 5;
            }
        }
        if (j % 2 == 1)
        {
            middle = plateform[j].x + plateform[j].size / 2;
            if (plateform[j].size % 2 == 0 && rand() % 2 == 0) middle--;
            map[middle % MAP_WIDTH][plateform[j].y] = 10 + tile;
        }

        if (plateform[j].arg > 0)
        {
            int x0, xf;
            switch (plateform[j].arg)
            {
                case 1: x0 = plateform[j].x - 1; xf = plateform[j].x + plateform[j].size - 1 - 1; break;
                case 2: x0 = plateform[j].x - 1; xf = plateform[j].x + plateform[j].size - 1 + 1; break;
                case 3: x0 = plateform[j].x + 1; xf = plateform[j].x + plateform[j].size - 1 - 1; break;
                case 4: x0 = plateform[j].x + 1; xf = plateform[j].x + plateform[j].size - 1 + 1; break;
            }
            if (x0 == xf)
            {
                plateform[j].arg = 0;
                xf--;
            }
            for (i = x0; i <= xf; i++)
            {
                int x = i % MAP_WIDTH;
                if (map[x][plateform[j].y+1] > 0) return false;
                if (map[(x + 2) % MAP_WIDTH][plateform[j].y+1] > 0) return false;
                if (map[x][plateform[j].y+1+1] > 0) return false;
                if (map[x][plateform[j].y+2+1] > 0) return false;

                if (i == x0)
                {
                    if (map[(x - 2 + MAP_WIDTH) % MAP_WIDTH][plateform[j].y+1] > 0) return false;
                    map[x][plateform[j].y+1] = 31 + tile * 5;
                }
                else if (i == xf)
                {
                    map[x][plateform[j].y+1] = 32 + tile * 5;
                }
                else
                {
                    int r = rand() % 18;
                    if (r == 0)
                        map[x][plateform[j].y+1] = 33 + tile * 5;
                    else if (r == 1)
                        map[x][plateform[j].y+1] = 34 + tile * 5;
                    else
                        map[x][plateform[j].y+1] = 30 + tile * 5;
                }
            }
        }
    }

    return true;
}

void JoustGameMap::generateRandomEnnemies(int level)
{
    botsToCome[0] = 0;
    botsToCome[1] = 0;
    botsToCome[2] = 0;
    botsToCome[3] = 0;

    if (level == 4) return;

    //int n = 3 + level / 3 + (level > 1) ? rand() % (level / 2) : 0;
    int n = 3 + level / 2;
    for (int i = 0; i < n; i++)
    {
        if (level >= 8 && rand() % 4 == 0)
            botsToCome[3]++;
        else if (level >= 5 && rand() % 3 == 0)
            botsToCome[2]++;
        else if (level >= 2 && rand() % 2 == 0)
            botsToCome[1]++;
        else
            botsToCome[0]++;
    }
}

std::vector<IntCoord> JoustGameMap::getGates()
{
    return gates;
}

int JoustGameMap::getDifferenceTile(int x, int y)
{
    return differenceMap[x][y];
}

int JoustGameMap::getBotToCome(int n) { return botsToCome[n]; }

void JoustGameMap::searchGates()
{
    gates.clear();
    for ( int i = 0 ; i < width ; i++)
        for ( int j = 0 ; j < height ; j++)
        {
            if (isPortal(i, j))
            {
                gates.push_back(IntCoord(i, j));
            }
        }

    for (unsigned int k = 0; k < gates.size(); k++)
    {
        //printf("(%d, %d)\n", gates[k].x, gates[k].y);
    }
}

bool JoustGameMap::isDownBlocking(int x, int y)
{
    if (y < 0) return true;
    if (!inMap(x, y)) return false;
    if (map[x][y] <= TILE_FIRE_OUT) return false;
    return true;
}

bool JoustGameMap::isUpBlocking(int x, int y)
{
    if (y < 0) return true;
    if (!inMap(x, y)) return false;
    if (map[x][y] <= TILE_FIRE_OUT) return false;
    return true;
}

bool JoustGameMap::isLeftBlocking(int x, int y)
{
    if (!inMap(x, y)) return false;
    if (map[x][y] <= TILE_FIRE_OUT) return false;
    return true;
}

bool JoustGameMap::isRightBlocking(int x, int y)
{
    if (!inMap(x, y)) return false;
    if (map[x][y] <= TILE_FIRE_OUT) return false;
    return true;
}

bool JoustGameMap::isLava(int x, int y)
{
    if (!inMap(x, y)) return false;
    if (map[x][y] >= TILE_FIRE_IN && map[x][y] <= TILE_FIRE_OUT) return true;
    return false;
}

bool JoustGameMap::isPortal(int x, int y)
{
    if (!inMap(x, y)) return false;
    if (map[x][y] >= TILE_PORTAL_IN && map[x][y] <= TILE_PORTAL_OUT) return true;
    return false;
}

bool JoustGameMap::isEmpty(int x, int y)
{
    if (!inMap(x, y)) return false;
    if (map[x][y] == TILE_EMPTY) return true;
    return false;
}
