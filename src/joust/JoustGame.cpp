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
                    int p = event.joystickButton.joystickId;
                    if (p < NPLAYERS_MAX)
                        lEngine->getPlayerInput(p)->jump = true;
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        LogicEngine::getLogicEngine()->startIntro();
                    }

                    bool processed = false;
                    // Jumping
                    for (int i = 0; i < NPLAYERS_MAX; ++i)
                    {
                        if (event.key.code == (sf::Keyboard::Key)(lEngine->getKeys(i).jump))
                        {
                            lEngine->getPlayerInput(i)->jump = true;
                            processed = true;
                            break;
                        }
                    }

                    // Pause
                    if ((!processed) && (event.key.code == sf::Keyboard::P))
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

void JoustGame::initResources(const std::string &libDir)
{
    ImageManager::getImageManager()->addImage((libDir + "media/hero0.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/hero1.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/hero2.png").c_str());

    ImageManager::getImageManager()->addImage((libDir + "mods/standard/media/tiles.png").c_str());

    ImageManager::getImageManager()->addImage((libDir + "media/ennemy0.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/ennemy1.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/ennemy2.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/ennemy3.png").c_str());

    ImageManager::getImageManager()->addImage((libDir + "media/egg16.png").c_str());

    ImageManager::getImageManager()->addImage((libDir + "media/gate64.png").c_str());

    ImageManager::getImageManager()->addImage((libDir + "mods/standard/media/bg.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/intro.jpg").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/blackPart.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/hud.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/select.png").c_str());

    ImageManager::getImageManager()->addImage((libDir + "media/life0.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/life1.png").c_str());
    ImageManager::getImageManager()->addImage((libDir + "media/life2.png").c_str());

    SoundManager::getSoundManager()->addSound((libDir + "media/sound/collisionJouster.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/jousterFall.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/collisionWall.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/gate.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/levelBegin.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/levelEnd.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/eggCrash.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/wingsFlap.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/step.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/burn.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/braking.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/lifeUp.wav").c_str());
    SoundManager::getSoundManager()->addSound((libDir + "media/sound/menuMove.wav").c_str());
}

void JoustGame::onRender()
{
    Game::onRender();
}



void JoustGame::onUpdate(float dt)
{
    Game::onUpdate(dt);
}
