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

#ifndef SELECTORENTITY_H_INCLUDED
#define SELECTORENTITY_H_INCLUDED

#include "../sfmlGame/Entity/SpriteEntity.h"

class SelectorEntity : public SpriteEntity
{
public:
    SelectorEntity(sf::Texture* image, float x, float y, int selected);

    int getSelected();
    void setSelected(int selected);

    virtual void render(sf::RenderWindow* app);
	//virtual void animate(float delay);

private:
    int selected;
};

#endif // SELECTORENTITY_H_INCLUDED
