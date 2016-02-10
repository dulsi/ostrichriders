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

#ifndef GAMECONSTANTS_H_INCLUDED
#define GAMECONSTANTS_H_INCLUDED

#include "Constants.h"

using namespace std;

class GameConstants
{
public:
    static GameConstants* getGameConstants();

    // general
    bool FULLSCREEN;

    // keys
    int CONTROL1_LEFT;
    int CONTROL1_RIGHT;
    int CONTROL1_JUMP;
    int CONTROL2_LEFT;
    int CONTROL2_RIGHT;
    int CONTROL2_JUMP;
    int CONTROL3_LEFT;
    int CONTROL3_RIGHT;
    int CONTROL3_JUMP;

    // physics
    float JOUSTER_WEIGHT;
    float JOUSTER_JUMP;
    float JOUSTER_HIT_JUMP;
    float JOUSTER_SPEED[JOUSTER_NB_SPEED];
    float SPEED_DELAY_WALKING;
    float SPEED_DELAY_BRAKING;
    float SPEED_DELAY_FLYING;
    float SPEED_DELAY_AIR_BRAKING;
    float JOUST_MAX_Y;

    string JOUST_USER_DIR;
    static string JOUST_DATA_DIR;

    void reloadFromFile(string mod);
private:
    GameConstants();
    bool loadFromFile(string file);
};

#endif // GameConstants_H_INCLUDED
