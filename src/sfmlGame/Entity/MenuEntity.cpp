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

#include "MenuEntity.h"
#include "../MediaManagers/SoundManager.h"

MenuEntity::MenuEntity(const sf::Font* font, int size, Menu* menu, float x, float y, float dy): GuiEntity(x, y)
{
    string = new sf::Text(L"", *font, (float)size);
    this->menu = menu;
    this->dy = dy;
    currentItem = 0;
    isButtonPressed = false;

    moveSound = -1;
}

MenuEntity::~MenuEntity()
{
    delete string;
}

bool MenuEntity::getButtonPressed()
{
    bool returnBool = isButtonPressed;
    isButtonPressed = false;
    return returnBool;
}

void MenuEntity::setMoveSound(int moveSound)
{
    this->moveSound = moveSound;
}

void MenuEntity::setMenu(Menu* menu)
{
    this->menu = menu;
}


void MenuEntity::render(sf::RenderWindow* app)
{

    //string->SetText(L"Menu");
    int n = menu->getNEntries();
    if (menu->getMenuType() == Menu::MENU_TYPE_ENTER_KEY)
        n = menu->getSelectedEntry() + 1;

    for (int i = 0; i < n; i++)
    {
        int yEntry = y + i * dy;

        if (menu->getSelectedEntry() == i)
        {
            string->setColor(sf::Color(255, 255, 255));
            if (menu->getMenuEntry(i)->getType() == MenuEntry::typeChoice)
                string->setString(L"< " + menu->getFullEntry(i) + L" >");
            else
                string->setString(menu->getFullEntry(i));
        }
        else
        {
            string->setColor(sf::Color(128, 128, 128));
            string->setString(menu->getFullEntry(i));
        }


        //string->SetSize(STRING_SIZE_MENU_ITEM);

        string->setPosition(x - string->getGlobalBounds().width / 2.f, yEntry);
        app->draw(*string);
    }

    //app->Draw(*string);
}

void MenuEntity::animate(float delay)
{
    GameEntity::animate(delay);
}

void MenuEntity::onEvent(sf::Event event)
{
    if (!isActive) return;

    if (menu->getMenuType() == Menu::MENU_TYPE_ENTER_KEY)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            menu->setKey(event.key.code);
        }
    }
    else
    {
        if (event.type == sf::Event::JoystickButtonPressed)
        {
            if (menu->getSelectedMenuEntry()->getType() == MenuEntry::typeButton)
            {
                isButtonPressed = true;
            }
        }

        if (event.type == sf::Event::JoystickMoved)
        {
            if (event.joystickMove.axis == sf::Joystick::X)
            {
                // left
                if (event.joystickMove.position < -20.0f)
                {
                    navigateLeft();
                }

                // right
                if (event.joystickMove.position > 20.0f)
                {
                    navigateRight();
                }
            }
            else
            {
                // up
                if (event.joystickMove.position < -20.0f)
                {
                    navigateUp();
                }

                // down
                if (event.joystickMove.position > 20.0f)
                {
                    navigateDown();
                }
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
            {
                if (menu->getSelectedMenuEntry()->getType() == MenuEntry::typeButton)
                {
                    isButtonPressed = true;
                }
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                navigateDown();
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                navigateUp();
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                navigateRight();
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                navigateLeft();
            }
        }
    }
}

void MenuEntity::navigateUp()
{
    int n = menu->getSelectedEntry() - 1;
    if (n < 0) n = menu->getNEntries() - 1;
    menu->setSelectedEntry(n);
    playSound(moveSound);
}

void MenuEntity::navigateDown()
{
    int n = menu->getSelectedEntry() + 1;
    if (n >= menu->getNEntries()) n = 0;
    menu->setSelectedEntry(n);
    playSound(moveSound);
}

void MenuEntity::navigateRight()
{
    if (menu->getSelectedMenuEntry()->getType() == MenuEntry::typeChoice)
    {
        menu->getSelectedMenuEntry()->selectNextChoice();
        playSound(moveSound);
    }
}

void MenuEntity::navigateLeft()
{
    if (menu->getSelectedMenuEntry()->getType() == MenuEntry::typeChoice)
    {
        menu->getSelectedMenuEntry()->selectPreviousChoice();
        playSound(moveSound);
    }
}

void MenuEntity::playSound(int sound)
{
    if (sound < 0) return;
    SoundManager::getSoundManager()->playSound(sound);
}
