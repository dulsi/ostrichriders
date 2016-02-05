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
    app->EnableKeyRepeat(false);
}

JoustGame::~JoustGame()
{
    //delete(app);
}

void JoustGame::startGame()
{
#ifndef _68X68

    ImageManager::getImageManager()->addImage((char*)"data/media/hero0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/hero1.png");

    //ImageManager::getImageManager()->addImage((char*)"data/media/piaf64.png");
    //ImageManager::getImageManager()->addImage((char*)"data/media/piaf2_64.png");

    ImageManager::getImageManager()->addImage((char*)"data/mods/standard/media/tiles.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy1.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy2.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/ennemy3.png");

    //ImageManager::getImageManager()->addImage((char*)"data/media/bot64_0.png");
    //ImageManager::getImageManager()->addImage((char*)"data/media/bot64_1.png");
    //ImageManager::getImageManager()->addImage((char*)"data/media/bot64_2.png");
    //ImageManager::getImageManager()->addImage((char*)"data/media/bot64_3.png");

#else

    ImageManager::getImageManager()->addImage((char*)"data/media/piaf68.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/piaf2_68.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/tiles.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/bot68_0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/bot68_1.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/bot68_2.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/bot68_3.png");

#endif

    ImageManager::getImageManager()->addImage((char*)"data/media/egg16.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/gate64.png");

    ImageManager::getImageManager()->addImage((char*)"data/mods/standard/media/bg.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/intro.jpg");
    ImageManager::getImageManager()->addImage((char*)"data/media/blackPart.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/hud.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/select.png");

    ImageManager::getImageManager()->addImage((char*)"data/media/life0.png");
    ImageManager::getImageManager()->addImage((char*)"data/media/life1.png");


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
    LogicEngine::getLogicEngine()->startIntro(); //startGame(2);

    // Start game loop
    printf("Starting %s %s\n", APP_NAME.c_str(), APP_VERSION.c_str());

    while (app->IsOpened())
    {
        // Process events
        sf::Event event;

        lEngine->initPlayerInputs();

        while (app->GetEvent(event))
        {
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                app->Close();

            if (event.Type == sf::Event::KeyPressed) {
                if (event.Key.Code == sf::Key::F10)
                {
                    sf::Image screen = app->Capture();
                    screen.SaveToFile("screenshot.jpg");
                }
            }

            lEngine->onEvent(event);

            if (LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_INTRO)
            {
                if (event.Type == sf::Event::KeyPressed) {
                    if (event.Key.Code == sf::Key::Escape)
                    {
                        app->Close();
                    }
                }
            }

            else if (LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_PLAYING
                    || LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_INTERLEVEL
                    || LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_CHOOSING)
            {
                if (event.Type == event.JoyButtonPressed)
                {
                    lEngine->getPlayerInput(0)->jump = true;
                }

                if (event.Type == sf::Event::KeyPressed) {
                    if (event.Key.Code == sf::Key::Escape)
                    {
                        LogicEngine::getLogicEngine()->startIntro();
                    }

                    // jumping (player 2)
                    else if (event.Key.Code == (sf::Key::Code)(lEngine->getKeys(1).jump))
                    {
                        lEngine->getPlayerInput(1)->jump = true;
                    }

                    else if (event.Key.Code == (sf::Key::Code)(lEngine->getKeys(0).jump))
                    {
                        lEngine->getPlayerInput(0)->jump = true;
                    }

                    // Pause
                    else if (event.Key.Code == sf::Key::P)
                    {
                        lEngine->pauseOrUnpause();
                    }
                }
            }

            else if (LogicEngine::getLogicEngine()->getGameState() == LogicEngine::GAME_GAMEOVER)
            {
                if (event.Type == sf::Event::KeyPressed || event.Type == event.JoyButtonPressed) {
                    //if (event.Key.Code == sf::Key::Escape)
                    {
                        if (lEngine->canEndGameOver()) lEngine->startIntro();
                    }
                }
            }
        }

        const sf::Input& input = app->GetInput();
        float joyX = input.GetJoystickAxis(0, sf::Joy::AxisX);

        lEngine->getPlayerInput(0)->left = input.IsKeyDown((sf::Key::Code)(lEngine->getKeys(0).left)) || joyX < -20.0f;
        lEngine->getPlayerInput(0)->right = input.IsKeyDown((sf::Key::Code)(lEngine->getKeys(0).right)) || joyX > 20.0f;
        lEngine->getPlayerInput(1)->left = input.IsKeyDown((sf::Key::Code)(lEngine->getKeys(1).left)); //|| joyX < -20.0f;
        lEngine->getPlayerInput(1)->right = input.IsKeyDown((sf::Key::Code)(lEngine->getKeys(1).right)); //|| joyX > 20.0f;


        if (!lEngine->isPausing())
        {
            onUpdate();
            lEngine->update(app->GetFrameTime());
        }

        onRender();

    }

    //delete map;
    quitGame();
}

void JoustGame::quitGame()
{

}

void JoustGame::onRender()
{
    Game::onRender();
}



void JoustGame::onUpdate()
{
    Game::onUpdate();
}
