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

#ifndef LOGICENGINE_H_INCLUDED
#define LOGICENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Constants.h"
#include "PlayerInput.h"
#include "PlayerEntity.h"
#include "BotEntity.h"
#include "EggEntity.h"
#include "JoustTileMapEntity.h"
#include "LifeEntity.h"
#include "RotatingTextEntity.h"
#include "SelectorEntity.h"
//#include "../sfmlGame/Model/GameMap.h"
#include "JoustGameMap.h"
#include "../sfmlGame/Entity/TextEntity.h"
#include "../sfmlGame/Entity/TextInputEntity.h"
#include "../sfmlGame/Model/GameScores.h"
#include "../sfmlGame/Entity/ScoresEntity.h"
#include "../sfmlGame/Model/Menu.h"
#include "../sfmlGame/Model/MenuEntry.h"
#include "../sfmlGame/Entity/MenuEntity.h"
#include "../sfmlGame/Entity/SurfaceEntity.h"

const int MENU_MAIN_START    = 0;
const int MENU_MAIN_PLAYERS  = 1;
const int MENU_MAIN_MOD      = 2;
const int MENU_MAIN_OPTIONS  = 3;
const int MENU_MAIN_EXIT     = 4;

const int MENU_OPTION_FULLSCREEN    = 0;
const int MENU_OPTION_CONTROLS1     = 1;
const int MENU_OPTION_CONTROLS2     = 2;
const int MENU_OPTION_CONTROLS3     = 3;
const int MENU_OPTION_BACK          = 4;

const int MENU_CONTROL_LEFT     = 0;
const int MENU_CONTROL_RIGHT    = 1;
const int MENU_CONTROL_JUMP     = 2;

class LogicEngine
{
public:
    static LogicEngine* getLogicEngine();

    void startIntro();
    void startChoosing();
    void startGame(int nPlayers);
    void startLevel();
    void loadLevel();
    void loadModData();

    void onPlayerDying(int player, int killer);
    void onTargetDying(BotEntity* botEntity, int killer);
    void onRemoveEgg(int eggType, int player);
    void onIncubate(EggEntity* entity);
    void onEggInLava();

    void generateEgg(float x, float y, int eggType);

    void update(float dt);
    void onEvent(sf::Event event);

    int getLives(int n);
    int getScore(int n);
    int getPlayerStatus(int n);
    int getGameState();
    PlayerEntity* getPlayerEntity(int n);
    PlayerInput* getPlayerInput(int n);
    int getNPlayers();
    int getLevel();
    int getTargets();

    bool isMultiplayer();
    bool canEndGameOver();

    void setRenderWindow(sf::RenderWindow* app);
    void setBraking(bool braking);

    void initPlayerInputs();

    void playSound(int n);
    void stopSound(int n);

    void pauseOrUnpause();
    bool isPausing();

    enum playerStatusEnum
    {
        PLAYER_STATUS_NEW,
        PLAYER_STATUS_PLAYING,
        PLAYER_STATUS_DEATH
    };

    enum gameStateEnum
    {
        GAME_INTRO,
        GAME_CHOOSING,
        GAME_PLAYING,
        GAME_INTERLEVEL,
        GAME_GAMEOVER,
        GAME_ENTERNAME
    };

    enum menuStateEnum
    {
        MENU_STATE_MAIN,
        MENU_STATE_OPTIONS,
        MENU_STATE_CONTROLS
    };

    struct keysStruct
    {
        int left;
        int right;
        int jump;
    };
    keysStruct getKeys(int n) { return keys[n]; }

private:
    LogicEngine();
    ~LogicEngine();

    // player related
    PlayerEntity* playerEntity[NPLAYERS_MAX];   // entity for the player
    int lives[NPLAYERS_MAX];                    // lives of the player
    int score[NPLAYERS_MAX];                    // player's score
    int playerStatus[NPLAYERS_MAX];             // player's status
    PlayerInput* playerInput[NPLAYERS_MAX];     // input set of the player
    float playerDelay[NPLAYERS_MAX];            // delay for the player
    RotatingTextEntity* scoreEntity[2];
    LifeEntity* lifeEntity[2];
    bool isSurvivor[NPLAYERS_MAX];
    float killDelay[NPLAYERS_MAX];
    int killCombo[NPLAYERS_MAX];
    std::string enteredName[NPLAYERS_MAX];
    bool isCooperative;

    TextEntity* levelEntity;
    TextEntity* levelTimeEntity;

    void startInterlevel();

    void generateEggsWave();

    // game related
    int nPlayers;   // how many players
    int level;      // current level
    //int levelMax;   // last level
    int gameState;
    GameScores* gameScores;

    float delay; // multi-usage delay
    bool isBraking;

    // level related
    int targets;    // how many targets to complete the level
    int botsToCome[N_BOTS];
    float levelTime;
    float nextBotTime;
    int levelTimeBonus;

    sf::RenderWindow* app;

    JoustGameMap* map;  // logic map
    JoustTileMapEntity* mapEntity;  // displayed map

    void createPlayer(int n);
    void createBot(int bot);

    void addScore(int player, int score);

    IntCoord getGate();
    bool arePlayersDead();
    void prepareGameOver();
    void prepareEnterName(int player);

    void giveBonus();

    bool isSound;

    int scoringPlayer;
    TextInputEntity* inputEntity;

    Menu* mainMenu;
    Menu* optionMenu;
    Menu* controlMenu;
    MenuEntity* menuEntity;
    void buildMenu();
    int menuState;

    std::string currentMod;

    bool isPause;
    SurfaceEntity* pauseBackEntity;
    TextEntity* pauseTextEntity;

    SelectorEntity* selectorEntity;

    bool invertedPlayers;
    int oldModChoice;

    keysStruct keys[3];

    void loadConfig();
    void saveConfig();
    bool isFullscreen;

    struct gameModeStruct
    {
        bool    randomMap;
        int     nMaps;
    } gameMode;
};

#endif // LOGICENGINE_H_INCLUDED
