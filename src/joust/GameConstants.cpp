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

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

#include "GameConstants.h"

GameConstants::GameConstants()
{
    loadFromFile("data/game_config.dat");
    loadFromFile("data/mods/standard/constants.dat");
}

 GameConstants* GameConstants::getGameConstants()
 {
   static GameConstants singleton;
   return &singleton;
 }

 void GameConstants::loadFromFile(string file)
 {
    ifstream f(file.c_str());
    if (!f.is_open()) return;

    //char c[64];
    string c;
    int integer;

	while (f >> c)
	{
	    // general
	    if (c.compare("FULLSCREEN") == 0) { f >> integer; FULLSCREEN = (integer > 0); }

	    // keys
	    if (c.compare("CONTROL1_LEFT")  == 0) { f >> integer; CONTROL1_LEFT = integer; }
	    if (c.compare("CONTROL1_RIGHT") == 0) { f >> integer; CONTROL1_RIGHT = integer; }
	    if (c.compare("CONTROL1_JUMP")  == 0) { f >> integer; CONTROL1_JUMP = integer; }
	    if (c.compare("CONTROL2_LEFT")  == 0) { f >> integer; CONTROL2_LEFT = integer; }
	    if (c.compare("CONTROL2_RIGHT") == 0) { f >> integer; CONTROL2_RIGHT = integer; }
	    if (c.compare("CONTROL2_JUMP")  == 0) { f >> integer; CONTROL2_JUMP = integer; }

        // physics
        if (c.compare("JOUSTER_WEIGHT") == 0) { f >> JOUSTER_WEIGHT; }
        if (c.compare("JOUST_MAX_Y") == 0) { f >> JOUST_MAX_Y; }
        if (c.compare("JOUSTER_JUMP") == 0) { f >> JOUSTER_JUMP; }
        if (c.compare("JOUSTER_HIT_JUMP") == 0) { f >> JOUSTER_HIT_JUMP; }
        if (c.compare("JOUSTER_SPEED_1") == 0) { f >> JOUSTER_SPEED[0]; }
        if (c.compare("JOUSTER_SPEED_2") == 0) { f >> JOUSTER_SPEED[1]; }
        if (c.compare("JOUSTER_SPEED_3") == 0) { f >> JOUSTER_SPEED[2]; }
        if (c.compare("JOUSTER_SPEED_4") == 0) { f >> JOUSTER_SPEED[3]; }
        if (c.compare("JOUSTER_SPEED_5") == 0) { f >> JOUSTER_SPEED[4]; }
        if (c.compare("SPEED_DELAY_WALKING") == 0) { f >> SPEED_DELAY_WALKING; }
        if (c.compare("SPEED_DELAY_BRAKING") == 0) { f >> SPEED_DELAY_BRAKING; }
        if (c.compare("SPEED_DELAY_FLYING") == 0) { f >> SPEED_DELAY_FLYING; }
        if (c.compare("SPEED_DELAY_AIR_BRAKING") == 0) { f >> SPEED_DELAY_AIR_BRAKING; }
	}

    f.close();
}

void GameConstants::reloadFromFile(string mod)
{
    loadFromFile("data/mods/standard/constants.dat");
    loadFromFile("data/mods/" + mod + "/constants.dat");
}
