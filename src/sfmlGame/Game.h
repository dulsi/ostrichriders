/**  This file is part of sfmlGame.
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

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Entity/EntityManager.h"

class Game
{
    public:
        Game(int screenWidth, int screenHeight, std::string windowsTitle = "Generic sfmlGame", bool fullScreen = false);
        virtual ~Game();

        virtual void startGame();
        virtual void quitGame();

        static float getAbsolutTime();
        static float getTimePassed();

    protected:
        virtual void onRender();     // screen and game items rendering
        virtual void onUpdate(float dt);

        int screenWidth;
        int screenHeight;

        sf::RenderWindow* app;
};

#endif // GAME_H_INCLUDED
