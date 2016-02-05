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

#ifndef MENUENTRY_INCLUDED
#define MENUENTRY_INCLUDED

#include <string>

const int CHOICES_MAX   = 32;
const int MENU_SIZE_MAX = 32;

using namespace std ;

/** menu item class
 ** will be used in menu
 ** example: an item [language] with choices [french], [english], [german]
 ** or an item [back to the game] */
class MenuEntry
{
public:
    MenuEntry(wstring text, int type);  // constructor: text of the item, type of the item (see bellow)
    ~MenuEntry() { }

    wstring getText() { return text; }
    wstring getChoice(int n) { return choice[n]; }
    int getType() { return type; }
    int getChoiceIndex() { return choiceIndex; }
    int getKey() { return key; }

    void setText(wstring text) { this->text=text; }
    void setKey(int keyCode) { this->key = keyCode; }
    void setType(int type) { this->type=type; }
    void setChoiceIndex(int choiceIndex) { this->choiceIndex=choiceIndex; }

    void addChoice(wstring choice);     // add a new choice

    void selectNextChoice();
    void selectPreviousChoice();

    wstring getFullText();  // return a string like "item text: choice text" (or just item text for a button)

    enum typeEnum { typeChoice, typeButton, typeKey, typeWaitKey };
private:
    wstring text;   // text of the menu item
    int type;       // type == typeChoice (menu item with different options, like languages, or "yes/no", ...
                    // or type == typeButton (to open a new menu, or get back, ...
    wstring choice[CHOICES_MAX];    // the different choices for this item (like "french", "english", "german"..)
    // choices
    int choiceIndex;    // the current choice
    int nChoices;       // the amount of choices available for this item
    // keys
    int key;
};

#endif // MENUENTRY_INCLUDED
