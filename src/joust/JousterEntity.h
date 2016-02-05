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

#ifndef JOUSTERENTITY_H_INCLUDED
#define JOUSTERENTITY_H_INCLUDED

#include "../sfmlGame/Entity/CollidingSpriteEntity.h"
#include "GameConstants.h"

// Basis class for Jouster
class JousterEntity : public CollidingSpriteEntity
{
public:
    JousterEntity(sf::Image* image, int spriteType, float x /*= 0.0f*/, float y /*= 0.0f*/);
    ~JousterEntity();

    int getSpeed();
    void setSpeed(int speed);

    virtual void render(sf::RenderWindow* app);
	virtual void animate(float delay);

	virtual void calculateBB();

    void collideEntityRight();
	void collideEntityLeft();

	void hitJump();

    void fallFromMount(bool generatesEgg = false);
    void fallInLava();

	enum statesEnum
	{
	    STATE_STANDING,
	    STATE_WALKING,
	    STATE_FALLING,
	    STATE_FLYING,
	    STATE_BRAKING,
	    STATE_AIR_BRAKING
	};

	enum spriteTypeEnum
	{
	    SPRITE_HERO,
	    SPRITE_ENNEMY
	};

protected:
    int speed;
    float speedDelay;
    float jumpDelay;

    int spriteType;

	virtual void exitMap(int direction);

    virtual void collideMapRight();
	virtual void collideMapLeft();
	virtual void collideEntity(CollidingSpriteEntity* entity);
	virtual void collideLava();

	virtual bool collidingWithLava();

	virtual void readCollidingEntity(CollidingSpriteEntity* entity);

	void findFrame();

	int state;

	bool wannaGoLeft;
	bool wannaGoRight;
	bool wannaJump;

	bool dirRight;
};

#endif // JOUSTERENTITY_H_INCLUDED
