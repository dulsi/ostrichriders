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

#include "Menu.h"

Menu::Menu(wstring title, int menuType)
{
    this->title = title;
    this->menuType = menuType;
    nEntries = 0;
    selectedEntry = 0;
}

Menu::~Menu()
{
    for (int i = 0; i < nEntries; i++)
        delete entry[i];
}

void Menu::addEntry (MenuEntry* entry)
{
    if (nEntries >= MENU_SIZE_MAX) return;

    this->entry[nEntries]=entry;
    nEntries++;
}

wstring Menu::getFullEntry(int n)
{
    return entry[n]->getFullText();
}

void Menu::setKey(int keyCode)
{
    entry[selectedEntry]->setKey(keyCode);
    entry[selectedEntry]->setType(MenuEntry::typeKey);
    selectedEntry++;
    if (selectedEntry >= nEntries)
    {
        selectedEntry--;
        allKeysDone = true;
    }
}

void Menu::init()
{
    if (menuType != MENU_TYPE_ENTER_KEY) return;

    selectedEntry = 0;
    allKeysDone = false;

    for (int i = 0; i < nEntries; i++)
        entry[i]->setType(MenuEntry::typeWaitKey);
}
