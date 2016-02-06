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

#ifndef JOUSTGAME_H_INCLUDED
#define JOUSTGAME_H_INCLUDED

#include "../sfmlGame/Game.h"
#include "PlayerInput.h"
#include "LogicEngine.h"

class JoustGame : public Game
{
    public:
        JoustGame();
        virtual ~JoustGame();

        virtual void startGame();
        virtual void quitGame();

    protected:
        virtual void onRender();     // screen and game items rendering
        virtual void onUpdate(float dt);

        //PlayerInput playerInput[2];
};

#endif // JOUSTGAME_H_INCLUDED
