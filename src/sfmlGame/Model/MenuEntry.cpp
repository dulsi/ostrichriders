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

#include "MenuEntry.h"

MenuEntry::MenuEntry(wstring text, int type)
{
    this->text = text;
    this->type = type;
    nChoices = 0;
    choiceIndex = 0;
}

void MenuEntry::addChoice(wstring item)
{
    if (nChoices >= CHOICES_MAX) return;

    choice[nChoices] = item;
    nChoices++;
}

void MenuEntry::selectNextChoice()
{
    choiceIndex++;
    if (choiceIndex >= nChoices) choiceIndex = 0;
}

void MenuEntry::selectPreviousChoice()
{
    choiceIndex--;
    if (choiceIndex < 0) choiceIndex=nChoices - 1;
}

wstring MenuEntry::getFullText()
{
    if (type == typeChoice)
    {
        return (text + L": " + choice[choiceIndex]);
    }
    else if (type == typeWaitKey)
    {
        return (text + L": ");
    }
    else if (type == typeKey)
    {
        return (text + L": " + wchar_t(key));
        //return (text + L": DONE");
    }
    return (text);
}
