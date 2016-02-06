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

#ifndef MENUENTITY_H_INCLUDED
#define MENUENTITY_H_INCLUDED

#include <string>

#include "GuiEntity.h"
#include "../Model/Menu.h"

class MenuEntity : public  GuiEntity
{
public:
    MenuEntity(const sf::Font* font, int size, Menu* menu, float x , float y, float dy);
    ~MenuEntity();

    bool getButtonPressed();
    void setMoveSound(int moveSound);
    void setMenu(Menu* menu);

    virtual void render(sf::RenderWindow* app);
	virtual void animate(float delay);

    virtual void onEvent(sf::Event event);

    virtual void navigateUp();
    virtual void navigateDown();
    virtual void navigateLeft();
    virtual void navigateRight();

    void playSound(int sound);

protected:
    sf::Text* string;

    float dy; // vertical distance between 2 menu entries
    int currentItem;
    Menu* menu;
    bool isButtonPressed;

    int moveSound;
};

#endif // MENUENTITY_H_INCLUDED
