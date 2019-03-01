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

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <string>

const std::string APP_NAME =      "Ostrich Riders";
const std::string APP_VERSION =   "0.6.5";

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int OFFSET_X = 0;
const int OFFSET_Y = 0;

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 22;

const int CLIENT_WIDTH = MAP_WIDTH * TILE_WIDTH;
const int CLIENT_HEIGHT = MAP_HEIGHT * TILE_HEIGHT;

//const float JOUSTER_WEIGHT = 390.0f;
//const float JOUSTER_JUMP = -180.0f;
//const float JOUSTER_HIT_JUMP = -50.0f;

//const int JOUSTER_NB_SPEED = 4;
//const float JOUSTER_SPEED[] = { 50.0f, 100.0f, 150.0f, 200.0f };
const int JOUSTER_NB_SPEED = 5;

const float JUMP_DELAY = 0.25f;
//const float JOUSTER_SPEED[] = { 55.0f, 110.0f, 165.0f, 220.0f, 275.0f };
//const float SPEED_DELAY = 0.15f;

const float MULTIKILL_DELAY = 1.5f;
const int KILL_COMBO_MAX = 4;

const int JOUSTER_WIDTH  = 64;
const int JOUSTER_HEIGHT = 64;

const int GATE_WIDTH  = 64;
const int GATE_HEIGHT = 64;

const int LIFE_WIDTH  = 20;
const int LIFE_HEIGHT = 20;

const int BB_LEFT    = 22;
const int BB_RIGHT   = 22;
const int BB_TOP     = 4;
const int BB_BOTTOM  = 31;

const int JOUSTER_KILLING_DISTANCE = 8;

const float JOUSTER_LATENCY = 0.5f;

const int EGG_WIDTH  = 16;
const int EGG_HEIGHT = 16;
const float EGG_VISCOSITY = 0.985f;
const float EGG_INCUBATION_DELAY_MIN = 8.0f;
const float EGG_INCUBATION_DELAY_MAX = 16.0f;

// LOGIC
const int NPLAYERS_MAX = 3;
const int INITIAL_LIVES = 4;

const int N_BOTS = 4;
const float BOT_DELAY = 1.0f;

const float REBORN_DELAY = 4.0f;

const int ROTATING_DELAY = 10;

// GAME
const float GAME_OVER_DELAY = 2.0f;
const float INTERLEVEL_DELAY = 4.0f;

// SCORING
const int BOT_SCORE[N_BOTS] = { 500, 750, 1000, 1500 };
const int EGG_SCORE[N_BOTS] = { 100, 200, 400, 600 };
const int HUMAN_SCORE = 1000;
const int SURVIVOR_SCORE = 1500;
const int COOPERATIVE_SCORE = 1500;

const int LIFE_UP = 40000;

const int LEVEL_TIME_BONUS = 4000;
const float LEVEL_TIME = 80.0f;

// TILES
const int TILE_FIRE_IN  = 1;
const int TILE_FIRE_OUT = 6;
const int TILE_PORTAL_IN  = 10;
const int TILE_PORTAL_OUT = 29;

// MEDIAMANAGERS
//IMAGES
const int IMAGE_PLAYER1     = 0;
const int IMAGE_PLAYER2     = 1;
const int IMAGE_PLAYER3     = 2;
const int IMAGE_TILES       = 3;
const int IMAGE_BOT_0       = 4;
const int IMAGE_BOT_1       = 5;
const int IMAGE_BOT_2       = 6;
const int IMAGE_BOT_3       = 7;
const int IMAGE_EGG         = 8;
const int IMAGE_GATE        = 9;
const int IMAGE_BACKGROUND  = 10;
const int IMAGE_INTRO       = 11;
const int IMAGE_BLACK_PART  = 12;
const int IMAGE_HUD         = 13;
const int IMAGE_SELECT      = 14;
const int IMAGE_LIFE0       = 15;
const int IMAGE_LIFE1       = 16;
const int IMAGE_LIFE2       = 17;

//SOUND
const int SOUND_COLLISION_WITH_JOUSTER  = 0;
const int SOUND_JOUSTER_FALL            = 1;
const int SOUND_COLLISION_WITH_WALL     = 2;
const int SOUND_GATE                    = 3;
const int SOUND_LEVEL_BEGIN             = 4;
const int SOUND_LEVEL_END               = 5;
const int SOUND_EGG_CRASH               = 6;
const int SOUND_WINGS_FLAP              = 7;
const int SOUND_STEP                    = 8;
const int SOUND_BURN                    = 9;
const int SOUND_BRAKING                 = 10;
const int SOUND_LIFE_UP                 = 11;
const int SOUND_MENU_MOVE               = 12;
/*
                                */

#endif // CONSTANTS_H_INCLUDED
