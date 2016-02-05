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

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "MenuEntry.h"

/** menu class
 ** will be used as a menu with different items
 ** example: option menu with items [language], [sound], [music], [skin], [effects] */
class Menu
{
public:
    Menu(wstring title, int menuType = MENU_TYPE_NORMAL);    // constructor with the title of the menu
    ~Menu();

    int getNEntries() { return nEntries; }
    wstring getTitle() { return title; }
    int getSelectedEntry() { return selectedEntry; }
    MenuEntry* getMenuEntry(int n) { return entry[n]; }
    MenuEntry* getSelectedMenuEntry() { return entry[selectedEntry]; }
    int getMenuType() { return menuType; }
    bool getAllKeysDone() { return allKeysDone; }

    void setKey(int keyCode);
    int getKey(int n) { return entry[n]->getKey(); }
    void setSelectedEntry(int myEntry) { selectedEntry = myEntry; }

    void addEntry(MenuEntry* entry);
    wstring getFullEntry(int n);

    void init();

    enum menuTypeEnum { MENU_TYPE_NORMAL, MENU_TYPE_ENTER_KEY };

private:
    wstring title;  // title of the menu
    MenuEntry* entry[MENU_SIZE_MAX];    // contents the various entries of the menu
    int nEntries;
    int selectedEntry;

    bool allKeysDone;

    int menuType;
};
#endif // MENU_H_INCLUDED
