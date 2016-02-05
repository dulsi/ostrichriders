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

#ifndef LIFEENTITY_H_INCLUDED
#define LIFEENTITY_H_INCLUDED

#include "../sfmlGame/Entity/SpriteEntity.h"

class LifeEntity : public SpriteEntity
{
public:
    LifeEntity(sf::Image* image, float x, float y, int lives);

    void setLives(int lives);

    virtual void render(sf::RenderWindow* app);
	//virtual void animate(float delay);

private:
    int lives;
};

#endif // LIFEENTITY_H_INCLUDED
