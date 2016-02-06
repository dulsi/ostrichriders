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

#ifndef MOUNTENTITY_INCLUDED
#define MOUNTENTITY_INCLUDED

#include "JousterEntity.h"

class MountEntity : public JousterEntity
{
public:
    MountEntity(sf::Texture* image, int spriteType, float x, float y);
    ~MountEntity();

    void setLeftDirection(bool isLeftDirection);

    virtual void animate(float delay);
    virtual void render(sf::RenderWindow* app);

    virtual void exitMap(int direction);

private:
    bool isLeftDirection;
    float botJumpDelay;
};

#endif // MOUNTENTITY_INCLUDED
