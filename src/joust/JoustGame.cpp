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

#include "Constants.h"
#include "JoustGame.h"
#include "JousterEntity.h"
#include "PlayerEntity.h"
#include "JoustTileMapEntity.h"
#include "GameConstants.h"
#include "LogicEngine.h"
#include "../sfmlGame/MediaManagers/ImageManager.h"
#include "../sfmlGame/MediaManagers/SoundManager.h"
//#include "../sfmlGame/Entity/TileMapEntity.h"

JoustGame::JoustGame(): Game(SCREEN_WIDTH,
                             SCREEN_HEIGHT,
                             APP_NAME + " " + APP_VERSION,
                             GameConstants::getGameConstants()->FULLSCREEN)
{
    app->setKeyRepeatEnabled(false);
}

JoustGame::~JoustGame()
{
}

void JoustGame::startGame()
{

    ImageManager::getImageManager()->addImage((char*)"data/media/hero0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/hero1.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/hero2.png");

    ImageManager::getImageManager()->addImage((char*)"data/mods/standard/media/tiles.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy1.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy2.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy3.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/egg16.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/gate64.png");

    ImageManager::getImageManager()->addImage((char*)"data/mods/standard/media/bg.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/intro.jpg");
    ImageManager::getImageManager()->addImage((char*)"data/media/blackPart.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/hud.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/select.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/life0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/life1.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/life2.png");


    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/collisionJouster.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/jousterFall.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/collisionWall.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/gate.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/levelBegin.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/levelEnd.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/eggCrash.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/wingsFlap.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/step.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/burn.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/braking.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/lifeUp.wav");
    SoundManager::getSoundManager()->addSound((char*)"data/media/sound/menuMove.wav");

    GameConstants::getGameConstants();

    LogicEngine* lEngine = LogicEngine::getLogicEngine();

    LogicEngine::getLogicEngine()->setRenderWindow(app);
    LogicEngine::getLogicEngine()->startIntro();

    // Start game loop
    printf("Starting %s %s\n", APP_NAME.c_str(), APP_VERSION.c_str());

    while (app->isOpen())
    {
        // Process events
        sf::Event event;

        lEngine->initPlayerInputs();

        while (app->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app->close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F10)
                {
                    sf::Image screen = app->capture();
                    screen.saveToFile("screenshot.jpg");
                }
            }

            lEngine->onEvent(event);

            if (LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_INTRO)
            {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        app->close();
                    }
                }
            }

            else if (LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_PLAYING
                    || LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_INTERLEVEL
                    || LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_CHOOSING)
            {
                if (event.type == sf::Event::JoystickButtonPressed)
                {
                    lEngine->getPlayerInput(0)->jump = true;
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        LogicEngine::getLogicEngine()->startIntro();
                    }

                    // jumping (player 2)
                    else if (event.key.code == (sf::Keyboard::Key)(lEngine->getKeys(2).jump))
                    {
                        lEngine->getPlayerInput(2)->jump = true;
                    }

                    else if (event.key.code == (sf::Keyboard::Key)(lEngine->getKeys(1).jump))
                    {
                        lEngine->getPlayerInput(1)->jump = true;
                    }

                    else if (event.key.code == (sf::Keyboard::Key)(lEngine->getKeys(0).jump))
                    {
                        lEngine->getPlayerInput(0)->jump = true;
                    }

                    // Pause
                    else if (event.key.code == sf::Keyboard::P)
                    {
                        lEngine->pauseOrUnpause();
                        getTimePassed();
                    }
                }
            }

            else if (LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_GAMEOVER)
            {
                if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed)
                {
                    //if (event.Key.Code == sf::Key::Escape)
                    {
                        if (lEngine->canEndGameOver()) lEngine->startIntro();
                    }
                }
            }
        }

        for (int i = 0; i < NPLAYERS_MAX; ++i)
        {
            float joyX = sf::Joystick::getAxisPosition(i, sf::Joystick::X);

            lEngine->getPlayerInput(i)->left = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(lEngine->getKeys(i).left)) || joyX < -20.0f;
            lEngine->getPlayerInput(i)->right = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(lEngine->getKeys(i).right)) || joyX > 20.0f;
        }


        if (!lEngine->isPausing())
        {
            float dt = getTimePassed();
            onUpdate(dt);
            lEngine->update(dt);
        }

        onRender();

    }

    quitGame();
}

void JoustGame::quitGame()
{

}

void JoustGame::onRender()
{
    Game::onRender();
}



void JoustGame::onUpdate(float dt)
{
    Game::onUpdate(dt);
}
