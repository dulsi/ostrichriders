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

#ifndef GATEENTITY_H_INCLUDED
#define GATEENTITY_H_INCLUDED

#include "../sfmlGame/Entity/SpriteEntity.h"

class GateEntity : public SpriteEntity
{
public:
    GateEntity(float x, float y, int gateColor = GATE_RED);
    ~GateEntity();

    //virtual void animate(float delay);
    virtual void render(sf::RenderWindow* app);

    enum gateColorEnum { GATE_BLUE, GATE_RED };
private:
    int gateColor;
};

#endif // GATEENTITY_H_INCLUDED
