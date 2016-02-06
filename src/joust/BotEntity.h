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

#ifndef BOTENTITY_H_INCLUDED
#define BOTENTITY_H_INCLUDED

#include "JousterEntity.h"

class BotEntity : public JousterEntity
{
public:
    BotEntity(sf::Texture* image, float x = 0.0f, float y = 0.0f, int aiType = 0);
    ~BotEntity();

    virtual void render(sf::RenderWindow* app);
    virtual void animate(float delay);
    virtual void onDying();

    int getAiType();

    bool repulse(float maxDist2);

    virtual void collideEntity(CollidingSpriteEntity* entity);
    virtual void collideLava();

protected:
    int aiType;
    bool isLeftDirection;
    float botJumpDelay;
    int aiPsy;
    float psyDelay;
    int psySpeed;

    int wannaTurn;
};

#endif // BOTENTITY_H_INCLUDED
