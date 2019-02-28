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

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

#include "LogicEngine.h"
#include "../sfmlGame/MediaManagers/ImageManager.h"
#include "../sfmlGame/MediaManagers/SoundManager.h"
#include "../sfmlGame/Entity/EntityManager.h"
#include "../sfmlGame/Entity/SurfaceEntity.h"
#include "BotEntity.h"
#include "EggEntity.h"
#include "GateEntity.h"
#include "FlyingScoreEntity.h"
#include "../defaultfont.h"


LogicEngine::LogicEngine() : map(NULL), arcade(false)
{
    printf("LogicEngine Singleton created\n");

    gameMode.randomMap = false;
    loadConfig();

    for (int i = 0; i < NPLAYERS_MAX; i++)
    {
        playerInput[i] = new PlayerInput();
        enteredName[i] = "";
    }
    gameScores = new GameScores(GameConstants::getGameConstants()->JOUST_USER_DIR, GameConstants::JOUST_DATA_DIR, "mods/standard/scores.dat");
    buildMenu();

    isSound = true;
    invertedPlayers = false;

    oldModChoice = 0;
}

LogicEngine::~LogicEngine()
{
    if (map)
        delete map;
}

 LogicEngine* LogicEngine::getLogicEngine()
 {
   static LogicEngine singleton;
   return &singleton;
 }

int LogicEngine::getLives(int n) { return lives[n]; }
int LogicEngine::getScore(int n) { return score[n]; }
int LogicEngine::getPlayerStatus(int n) { return playerStatus[n]; }
int LogicEngine::getGameState() { return gameState; }
PlayerInput* LogicEngine::getPlayerInput(int n) { return playerInput[n]; }
PlayerEntity* LogicEngine::getPlayerEntity(int n) { return playerEntity[n]; }
int LogicEngine::getNPlayers() { return nPlayers; }
int LogicEngine::getLevel() { return level; }
int LogicEngine::getTargets() { return targets; }

void LogicEngine::setRenderWindow(sf::RenderWindow* app) { this->app = app; }
void LogicEngine::setBraking(bool braking) { isBraking = braking; }

bool LogicEngine::isMultiplayer()
{
    if (nPlayers <= 1) return false;
    for (int i = 0; i < nPlayers; ++i)
    {
        if (playerStatus[i] == PLAYER_STATUS_DEATH)
            return false;
    }
    return true;
}

void LogicEngine::startIntro()
{
    EntityManager::getEntityManager()->clean();

    SpriteEntity* introEntity = new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_INTRO));
    introEntity->setX(SCREEN_WIDTH / 2);
    introEntity->setY(SCREEN_HEIGHT / 2);

    gameState = GAME_INTRO;
    menuState = MENU_STATE_MAIN;

    new ScoresEntity(&OstrichRiders::GetDefaultFont(), 17, gameScores, 30.f, 475.f, 242.f, 27.f);
    menuEntity = new MenuEntity(&OstrichRiders::GetDefaultFont(), 20, (arcade ? arcadeMenu : mainMenu), 512.f, 502.f, 42.f);
    menuEntity->setMoveSound(SOUND_MENU_MOVE);

    TextEntity* te0 = new TextEntity(&OstrichRiders::GetDefaultFont(), 20, 880.f, 477.f);
    te0->setText("Ostrich Riders V" + APP_VERSION);
    te0->setAlignment(TextEntity::ALIGN_CENTER);

    TextEntity* te1 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 520.f);
    te1->setText("Code: Seby");

    TextEntity* te2 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 550.f);
    te2->setText("Art: Suiland");

    TextEntity* te3 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 580.f);
    te3->setText("Released under GPLv3");

    TextEntity* te4 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 620.f);
    te4->setText(" - Controls for player 1");

    TextEntity* te5 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 650.f);
    te5->setText("[S][D] (move) - [J] (jump)");

    TextEntity* te6 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 680.f);
    te6->setText(" - Controls for player 2");

    TextEntity* te7 = new TextEntity(&OstrichRiders::GetDefaultFont(), 18 , 770.f, 710.f);
    te7->setText("Arrows - [Return] (jump)");

    //te0->setColor(TextEntity::COLOR_WHITE);
}

void LogicEngine::startChoosing()
{
    gameState = GAME_CHOOSING;
    for (int i = 0; i < NPLAYERS_MAX; i++)
        playerInput[i]->init();

    // black transparent screen
    SurfaceEntity* blackScreen = new SurfaceEntity(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);
    blackScreen->setColor(0, 0, 0, 255);
    //EntityManager::getEntityManager()->clean();


    // text (TODO: internationalisation)
    TextEntity* chooseTextEntity = new TextEntity(&OstrichRiders::GetDefaultFont(), 40, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150);
    chooseTextEntity->setText("Choose your character");
    chooseTextEntity->setAlignment(TextEntity::ALIGN_CENTER);
    chooseTextEntity->setColor(TextEntity::COLOR_WHITE);

    selectorEntity = new SelectorEntity(ImageManager::getImageManager()->getImage(IMAGE_SELECT), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, invertedPlayers ? 1 : 0);
}

void LogicEngine::startGame(int nPlayers)
{
    // disable repeat key (for jump)
    app->setKeyRepeatEnabled(false);
    isPause = false;

    printf("Starting the game\n");
    if (app == NULL)
    {
        printf("[ERROR] Cannot start a game without RenderWindow !\n");
        return;
    }

    //currentMod = "standard";
    currentMod = "sandbox";


    std::ostringstream stream;
    switch (mainMenu->getMenuEntry(MENU_MAIN_MOD)->getChoiceIndex())
    {
        case 1: currentMod = "random"; break;
        case 2: currentMod = "sandbox"; break;
        default: currentMod = "standard";
    }
    //string->SetText(intStream.str());

    // load mod data
    loadModData();

    // load mod constants
    GameConstants::getGameConstants()->reloadFromFile(currentMod);

    // load mod images

    // background
    if (!ImageManager::getImageManager()->reloadImage
                    (IMAGE_BACKGROUND, (GameConstants::JOUST_DATA_DIR + "mods/" + currentMod + "/media/bg.png").c_str()))
    {
        ImageManager::getImageManager()->reloadImage
                    (IMAGE_BACKGROUND, (GameConstants::JOUST_DATA_DIR + "mods/standard/media/bg.png").c_str());
    }

    // tiles
    if (!ImageManager::getImageManager()->reloadImage
                    (IMAGE_TILES, (GameConstants::JOUST_DATA_DIR + "mods/" + currentMod + "/media/tiles.png").c_str()))
    {
        ImageManager::getImageManager()->reloadImage
                    (IMAGE_TILES, (GameConstants::JOUST_DATA_DIR + "mods/standard/media/tiles.png").c_str());
    }

    // initialize values
    this->nPlayers = nPlayers;
    if (arcade)
        this->nPlayers = 2;

    EntityManager::getEntityManager()->clean();

    level = 1;
    // create the map
    if (map)
        delete map;
    map = new JoustGameMap(MAP_WIDTH, MAP_HEIGHT);

    // create player(s)
    for (int i = 0; i < NPLAYERS_MAX; i++)
    {
        //createPlayer(i, map);
        playerStatus[i] = ((i < nPlayers) ? PLAYER_STATUS_NEW : PLAYER_STATUS_DEATH);
        playerDelay[i] = 0.4f;
        lives[i] = ((i < nPlayers) ? INITIAL_LIVES : 0);
        score[i] = 0;
    }

    // create the tile map
    mapEntity = new JoustTileMapEntity(ImageManager::getImageManager()->getImage(IMAGE_TILES),
                                            map, TILE_WIDTH, TILE_HEIGHT, 10);
    mapEntity->setX(OFFSET_X);
    mapEntity->setY(OFFSET_Y);

    // hud
    new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_HUD), SCREEN_WIDTH / 2, SCREEN_HEIGHT - 32);

    // hud texts
    float yText = 730.0f;
    RotatingTextEntity *texts[2];
    texts[0] = new RotatingTextEntity(&OstrichRiders::GetDefaultFont(), 24, 15.0f, yText);
    texts[0]->setText(0, "Player 1");
    scoreEntity[0] = new RotatingTextEntity(&OstrichRiders::GetDefaultFont(), 24, 245.0f, yText);
    scoreEntity[0]->setText(0, 0);
    scoreEntity[0]->setAlignment(TextEntity::ALIGN_RIGHT);

    lifeEntity[0] = new LifeEntity(ImageManager::getImageManager()->getImage(invertedPlayers ? IMAGE_LIFE1 : IMAGE_LIFE0), 273.0f, yText + 3, &lives[0]);

    if (this->nPlayers > 1)
    {
        texts[1] = new RotatingTextEntity(&OstrichRiders::GetDefaultFont(), 24, 925.0f, yText);
        texts[1]->setText(0, "Player 2");
        scoreEntity[1] = new RotatingTextEntity(&OstrichRiders::GetDefaultFont(), 24, 902.0f, yText);
        scoreEntity[1]->setText(0, 0);
        scoreEntity[1]->setAlignment(TextEntity::ALIGN_RIGHT);

        lifeEntity[1] = new LifeEntity(ImageManager::getImageManager()->getImage(IMAGE_LIFE1), 690.0f, yText + 3, &lives[1]);
        for (int i = 2; i < nPlayers; ++i)
        {
            lifeEntity[i % 2]->addLives(ImageManager::getImageManager()->getImage(IMAGE_LIFE0 + i), &lives[i]);
            std::ostringstream intStream;
            intStream << "Player " << (i + 1);
            texts[i % 2]->setText(i / 2, intStream.str());
            scoreEntity[i % 2]->setText(i / 2, 0);
        }
    }

    TextEntity* text3 = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, 385.0f, yText);
    text3->setText(L"Wave");
    levelEntity = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, 454.0f, yText);
    levelEntity->setText(1);

    TextEntity* text4 = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, 528.0f, yText);
    text4->setText(L"Bonus");
    levelTimeEntity = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, 608.0f, yText);
    levelTimeEntity->setText(0);

    gameScores->resetNewScores();

    gameState = GAME_PLAYING;
    startLevel();
}

void LogicEngine::loadModData()
{
    string file = GameConstants::JOUST_DATA_DIR + "mods/" + currentMod + "/config.dat";
    ifstream f(file.c_str());

    //int nMaps = 0;
    if (!f.is_open())
    {
        ifstream f((GameConstants::JOUST_DATA_DIR + "mods/standard/config.dat").c_str());
    }

    string c;
    int integer;

	while (f >> c)
	{
	    if (c.compare("NUMBER_OF_MAPS")  == 0) { f >> gameMode.nMaps; }
	    if (c.compare("RANDOM_MAPS")     == 0) { f >> integer; gameMode.randomMap = (integer > 0); }
	}

	//levelMax = nMaps;

    f.close();
}

void LogicEngine::loadLevel()
{
    int level2Load = level;
    if (level2Load < 1) level2Load = 1;
    if (level2Load > gameMode.nMaps) level2Load = gameMode.nMaps;

    string s = GameConstants::JOUST_DATA_DIR + "mods/" + currentMod + "/maps/map";

    if (level2Load < 10)
    {
        s += '0';
        s += (char)((int)'0' + level2Load);
    }
    else
    {
        s += (char)((int)'0' + level / 10);
        s += (char)((int)'0' + level % 10);
    }
    s += ".dat";

    map->loadFromFile(s.c_str(), level2Load == 1);
}


void LogicEngine::startLevel()
{
    if (gameMode.randomMap)
    {
        map->nextRandomMap(level);
        mapEntity->generateFallingTiles();
    }
    else
    {
        if (level <= gameMode.nMaps)
        {
            loadLevel();
            mapEntity->generateFallingTiles();
        }
    }

    levelTime = 0.0f;
    levelTimeBonus = LEVEL_TIME_BONUS;
    levelEntity->setText(level);

    int i = 0;

    for (i = 0; i < N_BOTS; i++)
        botsToCome[i] = map->getBotToCome(i);

    nextBotTime = BOT_DELAY;
    targets = botsToCome[0] + botsToCome[1] + botsToCome[2] + botsToCome[3];

    if (targets == 0)
        generateEggsWave();

    for (i = 0; i < NPLAYERS_MAX; i++)
    {
        isSurvivor[i] = true;
        killDelay[i] = 0.0f;
        killCombo[i] = 0;
    }
    isCooperative = true;

    TextEntity* waveText = new TextEntity
                                        (&OstrichRiders::GetDefaultFont(), 48, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    std::ostringstream levelStream;
    levelStream << "WAVE " << level;
    waveText->setText(levelStream.str());
    //string->SetText(intStream.str());

    waveText->setAlignment(TextEntity::ALIGN_CENTER);
    waveText->setLifetime(3.0f);
    waveText->setColor(TextEntity::COLOR_FADING_WHITE);

    playSound(SOUND_LEVEL_BEGIN);
}

void LogicEngine::startInterlevel()
{
    gameState = GAME_INTERLEVEL;
    delay = INTERLEVEL_DELAY;
    giveBonus();    // time bonus

    float x1 = 300.0f;
    float x2 = x1 + 350.0f;
    float yTop = 320.0f;
    float dy = 50.0f;
    float xBorder = 15.0f;
    float yBorder = 22.0f;

    SurfaceEntity* backEntity = new SurfaceEntity(x1 - xBorder, yTop - yBorder, 500, 400);
    backEntity->setColor(0, 0, 0, 120);
    backEntity->setLifetime(INTERLEVEL_DELAY);


    float yNext = yTop;
    TextEntity* text1 = new TextEntity(&OstrichRiders::GetDefaultFont(), 25, x1, yNext);
    text1->setText(L"Wave annihilated");
    text1->setLifetime(INTERLEVEL_DELAY);

    yNext += dy;
    TextEntity* text2 = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, x1, yNext);
    text2->setText(L"Time bonus :");
    text2->setLifetime(INTERLEVEL_DELAY);
    TextEntity* text3 = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, x2, yNext);
    text3->setText(levelTimeBonus);
    text3->setLifetime(INTERLEVEL_DELAY);

    yNext += dy;

    bool multi = isMultiplayer();
    for (int i = 0; i < nPlayers; i++)
    {
        if ((playerStatus[i] != PLAYER_STATUS_DEATH) && (isSurvivor[i]))
        {
            TextEntity* survText = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, x1, yNext);
            if (multi)
            {
                std::ostringstream intStream;
                intStream << "Survival bonus (player " << (i + 1) << ") :";
                survText->setText(intStream.str());
            }
            else
            {
                survText->setText(L"Survival bonus :");
            }
            survText->setLifetime(INTERLEVEL_DELAY);
            TextEntity* survScoreText = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, x2, yNext);
            survScoreText->setText(SURVIVOR_SCORE);
            survScoreText->setLifetime(INTERLEVEL_DELAY);
            addScore(i, SURVIVOR_SCORE);
            yNext += dy;
        }
    }
    if (multi)
    {
        if (isCooperative)
        {
            TextEntity* coopText = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, x1, yNext);
            coopText->setText(L"Cooperative bonus :");
            coopText->setLifetime(INTERLEVEL_DELAY);
            TextEntity* coopScoreText = new TextEntity(&OstrichRiders::GetDefaultFont(), 24, x2, yNext);
            coopScoreText->setText(COOPERATIVE_SCORE);
            coopScoreText->setLifetime(INTERLEVEL_DELAY);
            for (int i = 0; i < nPlayers; i++)
            {
                addScore(i, COOPERATIVE_SCORE);
            }
            yNext += dy;
        }
    }

    backEntity->setSize(x2 - x1 + 75.0f + xBorder, yNext - dy - yTop + 2.0f * yBorder);
    playSound(SOUND_LEVEL_END);
}

void LogicEngine::addScore(int player, int score)
{
    int oldScore = this->score[player] / LIFE_UP;
    this->score[player] += score;

    if (oldScore < this->score[player] / LIFE_UP)
    {
        lives[player]++;
        playSound(SOUND_LIFE_UP);
        new FlyingScoreEntity(playerEntity[player]->getX(), playerEntity[player]->getY(), "LIFE UP");
    }
}

void LogicEngine::createPlayer(int n)
{
    IntCoord coords = getGate();
    float x = (float)(coords.x * TILE_WIDTH + OFFSET_X - TILE_WIDTH / 2 + JOUSTER_WIDTH / 2);
    float y = (float)(coords.y * TILE_HEIGHT + OFFSET_Y - TILE_HEIGHT / 2 - JOUSTER_HEIGHT / 2) + 16.0f;

    new GateEntity(x, y, GateEntity::GATE_BLUE);
    playSound(SOUND_GATE);

    int imageNumber = invertedPlayers ? IMAGE_PLAYER2 : IMAGE_PLAYER1;
    int playerNumber = n;

    switch (n)
    {
        case 1: imageNumber = invertedPlayers ? IMAGE_PLAYER1 : IMAGE_PLAYER2; break;
        case 2: imageNumber = IMAGE_PLAYER3; break;
    }

    playerEntity[n] = new PlayerEntity(ImageManager::getImageManager()->getImage(imageNumber),
                                            x, y, playerNumber);
    playerEntity[n]->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);

    playerEntity[n]->setPlayerInput(playerInput[n]);
}

void LogicEngine::createBot(int bot)
{
    IntCoord coords = getGate();
    float x = (float)(coords.x * TILE_WIDTH + OFFSET_X - TILE_WIDTH / 2 + JOUSTER_WIDTH / 2);
    float y = (float)(coords.y * TILE_HEIGHT + OFFSET_Y - TILE_HEIGHT / 2 - JOUSTER_HEIGHT / 2) + 16.0f;

    new GateEntity(x, y);
    playSound(SOUND_GATE);

    BotEntity* newBot = new BotEntity(ImageManager::getImageManager()->getImage(IMAGE_BOT_0 + bot),
                                            x, y, bot);
    newBot->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);

    botsToCome[bot]--;
    nextBotTime = BOT_DELAY;
}

IntCoord LogicEngine::getGate()
{
    int size = map->getGates().size();

    int n = 0;
    float bestD2 = 0.0f;

    for (int i = 0; i < size; i++)
    {
        float d2 = 10000000.0f;
        IntCoord coords(map->getGates()[i].x, map->getGates()[i].y);
        float x = (float)(coords.x * TILE_WIDTH + OFFSET_X - TILE_WIDTH / 2 + JOUSTER_WIDTH / 2);
        float y = (float)(coords.y * TILE_HEIGHT + OFFSET_Y - TILE_HEIGHT / 2 - JOUSTER_HEIGHT / 2);

        EntityManager::EntityList* entityList = EntityManager::getEntityManager()->getList();
        EntityManager::EntityList::iterator it;

        for (it = entityList->begin (); it != entityList->end ();)
        {
            GameEntity* entity = *it;

            JousterEntity* jEntity = dynamic_cast<JousterEntity*>(entity);
            if (jEntity != NULL)
            {
                float entityD2 = Vector2D(x, y).distance2(Vector2D(entity->getX(), entity->getY()), CLIENT_WIDTH);
                if (entityD2 < d2) d2 = entityD2;
            }
            it++;

        } // end for*/
        if (d2 > bestD2)
        {
            bestD2 = d2;
            n = i;
        }
    }

    return IntCoord(map->getGates()[n].x, map->getGates()[n].y);
}

void LogicEngine::initPlayerInputs()
{
    for (int i = 0; i < nPlayers; i++)
    {
        if (playerInput[i] != NULL)
            playerInput[i]->init();
    }
}

void LogicEngine::onPlayerDying(int player, int killer)
{
    lives[player]--;
    isSurvivor[player] = false;

    if (killer >= 0)
    {
        addScore(killer, HUMAN_SCORE);
        isCooperative = false;
    }

    if (lives[player] < 0)
    {
        playerStatus[player] = PLAYER_STATUS_DEATH;
    }
    else
    {
        playerStatus[player] = PLAYER_STATUS_NEW;
        playerDelay[player] = REBORN_DELAY;
    }
}

void LogicEngine::onRemoveEgg(int eggType, int player)
{
    playSound(SOUND_EGG_CRASH);
    targets--;
    if (player >= 0)
        addScore(player, EGG_SCORE[eggType]);
    if (targets == 0)
    {
        startInterlevel();
    }
}

void LogicEngine::onTargetDying(BotEntity* botEntity, int killer)
{
    int targetType = botEntity->getAiType();
    if (killer >= 0)
    {
        int scoreToAdd = 0;
        killCombo[killer]++;

        if (killCombo[killer] == 1)
        {
            scoreToAdd = BOT_SCORE[targetType];
            new FlyingScoreEntity(botEntity->getX(), botEntity->getY(), scoreToAdd);
        }
        else
        {
            int currentKillCombo = killCombo[killer];
            if (currentKillCombo > KILL_COMBO_MAX) currentKillCombo = KILL_COMBO_MAX;
            scoreToAdd = BOT_SCORE[targetType] * currentKillCombo;
            new FlyingScoreEntity(botEntity->getX(), botEntity->getY(), scoreToAdd, killCombo[killer]);
        }
        killDelay[killer] = MULTIKILL_DELAY;

        addScore(killer, scoreToAdd);
    }
}

void LogicEngine::onIncubate(EggEntity* entity)
{
    BotEntity* newBot = new BotEntity(ImageManager::getImageManager()->getImage(IMAGE_BOT_0 + entity->getEggType()),
                                            entity->getX(), entity->getY() - 30.0f, entity->getEggType());
    newBot->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);

    entity->setDying(true);

    for (int i = 0; i < 5; i++)
    {
        SpriteEntity* eggPart = new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_EGG),
                                                entity->getX(), entity->getY(),
                                                EGG_WIDTH / 2, EGG_HEIGHT / 2);
        eggPart->setVelocity(Vector2D (-30.0f + (float)rand() / (float)RAND_MAX * 60.0f,
                                            -30.0f + (float)rand() / (float)RAND_MAX * 60.0f));
        eggPart->setAngle((float)i * 90.0f);
        eggPart->setSpin(-300.0f + (float)rand() / (float)RAND_MAX * 600.0f);
        eggPart->setWeight(80.0f);
        eggPart->setLifetime(1.0f);
        eggPart->setFading(true);
    }
}

void LogicEngine::onEggInLava()
{
    playSound(SOUND_BURN);
    targets--;
    if (targets == 0)
    {
        startInterlevel();
    }
}

void LogicEngine::update(float dt)
{
    switch (gameState)
    {
        case GAME_INTRO:
        {
            if (arcade)
            {
                if (menuEntity->getButtonPressed())
                {
                    if (arcadeMenu->getSelectedEntry() == MENU_ARCADE_START)
                    {
                        startGame(1);
                    }
                    if (arcadeMenu->getSelectedEntry() == MENU_ARCADE_EXIT)
                    {
                        app->close();
                    }
                    break;
                }
                if (playerInput[1]->start)
                {
                    startGame(2);
                    break;
                }
                else if (playerInput[0]->start)
                {
                    startGame(1);
                    break;
                }
            }
            else
            {
                if (menuEntity->getButtonPressed())
                {
                    switch (menuState)
                    {
                        case MENU_STATE_MAIN:
                        {
                            if (mainMenu->getSelectedEntry() == MENU_MAIN_START)
                            {
                                int n = mainMenu->getMenuEntry(MENU_MAIN_PLAYERS)->getChoiceIndex() + 1;
                                if (n == 1)
                                    startChoosing();
                                else
                                    startGame(n);
                            }
                            if (mainMenu->getSelectedEntry() == MENU_MAIN_OPTIONS)
                            {
                                menuEntity->setMenu(optionMenu);
                                menuState = MENU_STATE_OPTIONS;
                            }
                            if (mainMenu->getSelectedEntry() == MENU_MAIN_EXIT)
                            {
                                app->close();
                            }
                            break;
                        }

                        case MENU_STATE_OPTIONS:
                        {
                            if (optionMenu->getSelectedEntry() == MENU_OPTION_CONTROLS1
                             || optionMenu->getSelectedEntry() == MENU_OPTION_CONTROLS2
                             || optionMenu->getSelectedEntry() == MENU_OPTION_CONTROLS3)
                            {
                                menuEntity->setMenu(controlMenu);
                                controlMenu->init();
                                menuState = MENU_STATE_CONTROLS;
                            }
                            if (optionMenu->getSelectedEntry() == MENU_OPTION_BACK)
                            {
                                isFullscreen = optionMenu->getMenuEntry(MENU_OPTION_FULLSCREEN)->getChoiceIndex() == 0;
                                menuEntity->setMenu(mainMenu);
                                menuState = MENU_STATE_MAIN;

                                saveConfig();
                            }
                            break;
                        }

                        case MENU_STATE_CONTROLS:
                        {
                            /*if (controlMenu->getAllKeysDone())
                            {
                                menuEntity->setMenu(controlMenu);
                                menuState = MENU_STATE_CONTROLS;
                            }
                            break;*/
                        }
                    }
                }

                if (oldModChoice != mainMenu->getMenuEntry(MENU_MAIN_MOD)->getChoiceIndex())
                {
                    oldModChoice = mainMenu->getMenuEntry(MENU_MAIN_MOD)->getChoiceIndex();
                    if (oldModChoice == 0)
                    {
                        gameScores->setFilename("mods/standard/scores.dat");
                    }
                    else if (oldModChoice == 1)
                    {
                        gameScores->setFilename("mods/random/scores.dat");
                    }
                    else if (oldModChoice == 2)
                    {
                        gameScores->setFilename("mods/sandbox/scores.dat");
                    }
                }

                if (menuState == MENU_STATE_CONTROLS)
                {
                    if (controlMenu->getAllKeysDone())
                    {
                        menuEntity->setMenu(optionMenu);
                        menuState = MENU_STATE_OPTIONS;

                        int p = 0;
                        if (optionMenu->getSelectedEntry() == MENU_OPTION_CONTROLS2)
                            p = 1;
                        if (optionMenu->getSelectedEntry() == MENU_OPTION_CONTROLS3)
                            p = 2;
                        keys[p].left   = controlMenu->getKey(MENU_CONTROL_LEFT);
                        keys[p].right  = controlMenu->getKey(MENU_CONTROL_RIGHT);
                        keys[p].jump   = controlMenu->getKey(MENU_CONTROL_JUMP);
                    }
                    break;
                }
            }

            break;
        }

        case GAME_CHOOSING:
        {
            if (playerInput[0]->left || playerInput[1]->left)
            {
                if (selectorEntity->getSelected() == 1)
                {
                    selectorEntity->setSelected(0);
                    playSound(SOUND_MENU_MOVE);
                }
            }
            if (playerInput[0]->right || playerInput[1]->right)
            {
                if (selectorEntity->getSelected() == 0)
                {
                    selectorEntity->setSelected(1);
                    playSound(SOUND_MENU_MOVE);
                }
            }

            if (playerInput[0]->jump || playerInput[1]->jump)
            {
                invertedPlayers = (selectorEntity->getSelected() == 1);
                startGame(1);
            }
            break;
        }

        case GAME_PLAYING:
        {
            levelTime += dt;
            if (levelTime >= LEVEL_TIME)
            {
                levelTimeBonus = 0;
            }
            else
            {
                levelTimeBonus = LEVEL_TIME_BONUS - (int)((float)LEVEL_TIME_BONUS * (levelTime / (float)LEVEL_TIME));
                levelTimeBonus -= levelTimeBonus % 5;
                levelTimeEntity->setText(levelTimeBonus);
            }

            int i;
            for (i = 0; i < nPlayers; i++)
            {
                if ((playerStatus[i] == PLAYER_STATUS_DEATH) && (playerInput[i]->start))
                {
                    playerStatus[i] = PLAYER_STATUS_NEW;
                    playerDelay[i] = 0.4f;
                    lives[i] = INITIAL_LIVES;
                    score[i] = 0;
                    isSurvivor[i] = true;
                    killDelay[i] = 0.0f;
                    killCombo[i] = 0;
                }
                if (killDelay[i] > 0.0f)
                {
                    killDelay[i] -= dt;
                    if (killDelay[i] <= 0.0f) killCombo[i] = 0;
                }
            }

            bool out = false;
            for (i = 0; i < N_BOTS && !out; i++)
            {
                if (botsToCome[i] > 0)
                {
                    nextBotTime -= dt;
                    if (nextBotTime <= 0.0f)
                    {
                        createBot(i);
                    }
                    out = true;
                }
            }
        }
        case GAME_INTERLEVEL:
        {
            for (int i = 0; i < nPlayers; i++)
            {
                if (playerStatus[i] == PLAYER_STATUS_NEW)
                {
                    playerDelay[i] -= dt;
                    if (playerDelay[i] <= 0.0f)
                    {
                        createPlayer(i);
                        playerStatus[i] = PLAYER_STATUS_PLAYING;
                    }
                }
                scoreEntity[i % 2]->setText(i / 2, score[i]);
            }

            if (arePlayersDead())
            {
                prepareGameOver();
            }
            if (gameState == GAME_INTERLEVEL)
            {
                delay -= dt;
                if (delay <= 0.0f)
                {
                    gameState = GAME_PLAYING;
                    level++;
                    startLevel();
                }
            }

            if (isBraking)
            {
                playSound(SOUND_BRAKING);
            }
            else
            {
                stopSound(SOUND_BRAKING);
            }
            isBraking = false;
            break;
        }

        case GAME_GAMEOVER:
        {
            if (delay >= 0.0f)
            {
                delay-=dt;
                if (delay < 0.0f)
                {
                    TextEntity* clickText = new TextEntity
                                                (&OstrichRiders::GetDefaultFont(), 24, SCREEN_WIDTH / 2, 420);
                    clickText->setText(L"Press a key to continue");
                    clickText->setAlignment(TextEntity::ALIGN_CENTER);
                    clickText->setColor(TextEntity::COLOR_BLINKING_WHITE);
                }
            }


            break;
        }

        case GAME_ENTERNAME:
        {
            if (inputEntity->getReturned())
            {
                enteredName[scoringPlayer] = inputEntity->getInputText();
                gameScores->addScore(score[scoringPlayer], inputEntity->getInputText());
                inputEntity->setDying(true);

                for (int i = scoringPlayer + 1; i < nPlayers; i++)
                {
                    if (score[i] > gameScores->getScore(9))
                    {
                        prepareEnterName(i);
                        inputEntity->setAge(4.0f);
                        return;
                    }
                }
                startIntro();
            }


            break;
        }
    }
}

void LogicEngine::onEvent(sf::Event event)
{
    EntityManager::getEntityManager()->onEvent(event);
}

bool LogicEngine::canEndGameOver()
{
    if (gameState == GAME_GAMEOVER && delay <= 0.0f) return true;
    else return false;
}

bool LogicEngine::arePlayersDead()
{
   for (int i = 0; i < nPlayers; i++)
    {
        if (playerStatus[i] != PLAYER_STATUS_DEATH) return false;
    }
    return true;
}

void LogicEngine::prepareGameOver()
{
    TextEntity* gameOverText = new TextEntity
                            (&OstrichRiders::GetDefaultFont(), 48, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    gameOverText->setText(L"GAME OVER");
    gameOverText->setAlignment(TextEntity::ALIGN_CENTER);

    if (!arcade)
    {
        for (int i = 0; i < nPlayers; i++)
        {
            if (score[i] > gameScores->getScore(9))
            {
                prepareEnterName(i);
                return;
            }
        }
    }

    gameState = GAME_GAMEOVER;
    delay = GAME_OVER_DELAY;
}

void LogicEngine::prepareEnterName(int player)
{
    app->setKeyRepeatEnabled(true);

    gameState = GAME_ENTERNAME;
    scoringPlayer = player;

    //if (inputEntity != NULL) delete inputEntity;
    inputEntity = new TextInputEntity(&OstrichRiders::GetDefaultFont(), 20, 370.0f, 450.0f);
    std::ostringstream intStream;
    intStream << "Player " << (scoringPlayer + 1) << ", enter you name: ";
    inputEntity->setPreText(intStream.str());
    inputEntity->setInputText(enteredName[player]);
}

void LogicEngine::giveBonus()
{
    for (int i = 0; i < nPlayers; i++)
    {
        if (playerStatus[i] != PLAYER_STATUS_DEATH)
        {
            addScore(i, levelTimeBonus);
        }
    }
}

void LogicEngine::generateEgg(float x, float y, int eggType)
{
    EggEntity* eggEntity = new EggEntity(ImageManager::getImageManager()->getImage(IMAGE_EGG), x, y);
    eggEntity->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);
    eggEntity->setEggType(eggType);
}

void LogicEngine::generateEggsWave()
{

    for (int j = 1; j < map->getHeight() - 1; j++)
        for (int i = 0; i < map->getWidth(); i++)
        {
            if (map->isEmpty(i, j) && !map->isEmpty(i, j + 1) && !map->isLava(i, j + 1))
                {
                    generateEgg((float)(OFFSET_X + i * TILE_WIDTH + TILE_WIDTH / 2),
                                (float)(OFFSET_Y + j * TILE_HEIGHT + TILE_HEIGHT / 2),
                                rand() % 2);
                    targets++;
                    i++;
                }

        }
}

void LogicEngine::playSound(int n)
{
    if (!isSound) return;
    SoundManager::getSoundManager()->playSound(n);
}

void LogicEngine::stopSound(int n)
{
    if (!isSound) return;
    SoundManager::getSoundManager()->stopSound(n);
}

void LogicEngine::buildMenu()
{
    mainMenu = new Menu(L"Menu");

    MenuEntry* entryStartGame = new MenuEntry(L"Start game", MenuEntry::typeButton);
    mainMenu->addEntry(entryStartGame);

    MenuEntry* entryPlayers = new MenuEntry(L"Number of players", MenuEntry::typeChoice);
    entryPlayers->addChoice(L"1");
    entryPlayers->addChoice(L"2");
    entryPlayers->addChoice(L"3");
    mainMenu->addEntry(entryPlayers);

    MenuEntry* entryMod = new MenuEntry(L"Mod", MenuEntry::typeChoice);
    entryMod->addChoice(L"standard");
    entryMod->addChoice(L"random");
    entryMod->addChoice(L"sandbox");
    mainMenu->addEntry(entryMod);

    MenuEntry* entryOptions = new MenuEntry(L"Options", MenuEntry::typeButton);
    mainMenu->addEntry(entryOptions);

    MenuEntry* entryExitGame = new MenuEntry(L"Exit", MenuEntry::typeButton);
    mainMenu->addEntry(entryExitGame);

    arcadeMenu = new Menu(L"Menu");

    MenuEntry* entryStartGame2 = new MenuEntry(L"Press 1P or 2P", MenuEntry::typeButton);
    arcadeMenu->addEntry(entryStartGame2);

    MenuEntry* entryExitGame2 = new MenuEntry(L"Exit", MenuEntry::typeButton);
    arcadeMenu->addEntry(entryExitGame2);


    optionMenu = new Menu(L"Options");
    MenuEntry* entryFullscreen = new MenuEntry(L"Fullscreen", MenuEntry::typeChoice);
    entryFullscreen->addChoice(L"Yes");
    entryFullscreen->addChoice(L"No");
    if (!isFullscreen) entryFullscreen->setChoiceIndex(1);
    optionMenu->addEntry(entryFullscreen);
    MenuEntry* entryControls1 = new MenuEntry(L"Configure controls (P1)", MenuEntry::typeButton);
    optionMenu->addEntry(entryControls1);
    MenuEntry* entryControls2 = new MenuEntry(L"Configure controls (P2)", MenuEntry::typeButton);
    optionMenu->addEntry(entryControls2);
    MenuEntry* entryControls3 = new MenuEntry(L"Configure controls (P3)", MenuEntry::typeButton);
    optionMenu->addEntry(entryControls3);
    MenuEntry* entryBack = new MenuEntry(L"Back", MenuEntry::typeButton);
    optionMenu->addEntry(entryBack);

    controlMenu = new Menu(L"Configure keys", Menu::MENU_TYPE_ENTER_KEY);
    MenuEntry* key1 = new MenuEntry(L"Press key for [left]", MenuEntry::typeWaitKey);
    controlMenu->addEntry(key1);
    MenuEntry* key2 = new MenuEntry(L"Press key for [right]", MenuEntry::typeWaitKey);
    controlMenu->addEntry(key2);
    MenuEntry* key3 = new MenuEntry(L"Press key for [jump]", MenuEntry::typeWaitKey);
    controlMenu->addEntry(key3);
}

void LogicEngine::pauseOrUnpause()
{
    if (isPause)
    {
        isPause = false;
        pauseBackEntity->setDying(true);
        pauseTextEntity->setDying(true);
    }
    else
    {
        isPause = true;
        pauseBackEntity = new SurfaceEntity(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);
        pauseBackEntity->setColor(0, 0, 0, 160);

        pauseTextEntity = new TextEntity(&OstrichRiders::GetDefaultFont(), 52, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        pauseTextEntity->setText("PAUSE");
        pauseTextEntity->setAlignment(TextEntity::ALIGN_CENTER);
        pauseTextEntity->setColor(TextEntity::COLOR_WHITE);
    }
}

bool LogicEngine::isPausing()
{
    return isPause;
}

void LogicEngine::loadConfig()
{
    isFullscreen   = GameConstants::getGameConstants()->FULLSCREEN;
    keys[0].left   = GameConstants::getGameConstants()->CONTROL1_LEFT;
    keys[0].right  = GameConstants::getGameConstants()->CONTROL1_RIGHT;
    keys[0].jump   = GameConstants::getGameConstants()->CONTROL1_JUMP;
    keys[1].left   = GameConstants::getGameConstants()->CONTROL2_LEFT;
    keys[1].right  = GameConstants::getGameConstants()->CONTROL2_RIGHT;
    keys[1].jump   = GameConstants::getGameConstants()->CONTROL2_JUMP;
    keys[2].left   = GameConstants::getGameConstants()->CONTROL3_LEFT;
    keys[2].right  = GameConstants::getGameConstants()->CONTROL3_RIGHT;
    keys[2].jump   = GameConstants::getGameConstants()->CONTROL3_JUMP;
}

void LogicEngine::saveConfig()
{
    ofstream f((GameConstants::getGameConstants()->JOUST_USER_DIR + "game_config.dat").c_str());
    if (!f.is_open()) return;

    f << "FULLSCREEN " << (isFullscreen ? "1\n" : "0\n");

    f << "CONTROL1_LEFT "  << keys[0].left  << endl;
    f << "CONTROL1_RIGHT " << keys[0].right << endl;
    f << "CONTROL1_JUMP "  << keys[0].jump  << endl;

    f << "CONTROL2_LEFT "  << keys[1].left  << endl;
    f << "CONTROL2_RIGHT " << keys[1].right << endl;
    f << "CONTROL2_JUMP "  << keys[1].jump  << endl;

    f << "CONTROL3_LEFT "  << keys[2].left  << endl;
    f << "CONTROL3_RIGHT " << keys[2].right << endl;
    f << "CONTROL3_JUMP "  << keys[2].jump  << endl;

    f.close();
}
