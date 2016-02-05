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

#include "JousterEntity.h"
#include "MountEntity.h"
#include "FallingRiderEntity.h"
#include "BurningJousterEntity.h"
#include "LogicEngine.h"
#include "Constants.h"

JousterEntity::JousterEntity(sf::Image* image, int spriteType, float x, float y)
                                    : CollidingSpriteEntity(image, x, y, JOUSTER_WIDTH, JOUSTER_HEIGHT)
{
    this->spriteType = spriteType;

    weight =        GameConstants::getGameConstants()->JOUSTER_WEIGHT;
    normalWeight =  weight;
    maxY = GameConstants::getGameConstants()->JOUST_MAX_Y;

    speed = 0;
    speedDelay = 0.0f;
    jumpDelay = 0.0f;

    state = STATE_FALLING;

    dirRight = true;
}

JousterEntity::~JousterEntity()
{
}

int JousterEntity::getSpeed()
{
    return speed;
}

void JousterEntity::setSpeed(int speed)
{
    this->speed = speed;
    //speedDelay = GameConstants::getGameConstants()->SPEED_DELAY;
    speedDelay = 0.0f;
    if (speed == 0) velocity.x = 0.0f;
    else if (speed > 0) velocity.x = GameConstants::getGameConstants()->JOUSTER_SPEED[speed - 1];
    else velocity.x = -GameConstants::getGameConstants()->JOUSTER_SPEED[-speed - 1];
}

void JousterEntity::render(sf::RenderWindow* app)
{
    if ((int)velocity.x < 0) dirRight = false;
    if ((int)velocity.x > 0) dirRight = true;

    // rendering the mount
    findFrame();
    sprite.FlipX(!dirRight);
    //CollidingSpriteEntity::render(app);
    sprite.SetSubRect(sf::IntRect(frame * width, 0, (frame + 1) * width, height));
    sprite.SetX(x);
    sprite.SetY(y);
    if (frame == 5) sprite.SetY(y + 4.0f);

    app->Draw(sprite);


    // rendering the rider
    int dx = 0;
    sprite.FlipX(false);
    if (!dirRight) dx = width;
    sprite.SetSubRect(sf::IntRect(dx, height, dx + width, 2 * height));
    //if (frame == 0) sprite.SetY(y - 4.0f);
    //if (frame >= 6 && frame <= 8) sprite.SetY(y + 3.0f);

    app->Draw(sprite);
}

void JousterEntity::animate(float delay)
{
    speedDelay += delay;
    jumpDelay -= delay;

    if (collidingWithLava())
    {
        collideLava();
    }

    if (wannaJump && jumpDelay <= 0.0f)
    {
        LogicEngine::getLogicEngine()->playSound(SOUND_WINGS_FLAP);
        velocity.y = GameConstants::getGameConstants()->JOUSTER_JUMP;
        weight = GameConstants::getGameConstants()->JOUSTER_WEIGHT;

        jumpDelay = JUMP_DELAY;

        //age = 6.0f;
    }

    bool onGround = isOnGround();

    if (wannaGoRight)
    {
        if (speed > 1 && speed < JOUSTER_NB_SPEED)
        {
            if ((onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_WALKING)
                    || (!onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_FLYING))
                {
                    setSpeed(speed + 1);
                }
        }
        //else if (speed == 0)
        //{
        //    setSpeed(speed + 1);
        //}
        else if (speed <= 1)
        {
            if ((onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_BRAKING)
                    || (!onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_AIR_BRAKING))
                {
                    setSpeed(speed + 1);
                }
        }
    }

    if (wannaGoLeft)
    {
        if (speed < -1 && speed > -JOUSTER_NB_SPEED)
        {
            if ((onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_WALKING)
                    || (!onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_FLYING))
                {
                    setSpeed(speed - 1);
                }
        }
        //else if (speed == 0)
        //{
        //    setSpeed(speed - 1);
        //}
        else if (speed >= -1)
        {
            if ((onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_BRAKING)
                    || (!onGround && speedDelay >= GameConstants::getGameConstants()->SPEED_DELAY_AIR_BRAKING))
                {
                    setSpeed(speed - 1);
                }
        }
    }

    CollidingSpriteEntity::animate(delay);
    testSpriteCollisions();

    if (isOnGround()) state = (speed == 0) ? STATE_STANDING : STATE_WALKING;
    else if (velocity.y > 0.0f) state = STATE_FALLING;
    else state = STATE_FLYING;

    if ( (speed > 0 && wannaGoLeft) || (speed < 0 && wannaGoRight) )
    {
        if (state == STATE_WALKING)
            state = STATE_BRAKING;
        else
            state = STATE_AIR_BRAKING;
    }
    /*
    if (state == STATE_WALKING)
    {
        if ( (speed > 0 && wannaGoLeft) || (speed < 0 && wannaGoRight) )
            state = STATE_BRAKING;
    }
    */
}

void JousterEntity::calculateBB()
{
    boundingBox.Left = (int)x - BB_LEFT;
    boundingBox.Right = (int)x + BB_RIGHT;
    boundingBox.Top = (int)y - BB_TOP;
    boundingBox.Bottom = (int)y + BB_BOTTOM;
}

void JousterEntity::exitMap(int direction)
{
    switch (direction)
    {
    case DIRECTION_LEFT:
        x = (float)(map->getWidth() * (tileWidth - 1) + width / 2) + (float)offsetX;
        break;

    case DIRECTION_RIGHT:
        x = 1.0f - (float)width / 2.0f + (float)offsetX;
        break;
    }
}

void JousterEntity::collideMapRight()
{
    if (speed <= -2 || speed >= 2) LogicEngine::getLogicEngine()->playSound(SOUND_COLLISION_WITH_WALL);
    if (speed > 3) setSpeed(-2);
    else if (speed > 1) setSpeed(-1);
    else setSpeed(0);
}

void JousterEntity::collideMapLeft()
{
    if (speed <= -2 || speed >= 2) LogicEngine::getLogicEngine()->playSound(SOUND_COLLISION_WITH_WALL);
    if (speed < -3) setSpeed(2);
    else if (speed < -1) setSpeed(1);
    else setSpeed(0);
}

void JousterEntity::readCollidingEntity(CollidingSpriteEntity* entity)
{
    JousterEntity* jousterEntity = dynamic_cast<JousterEntity*>(entity);
    if (jousterEntity == NULL) return;
    if (jousterEntity == this) return;

    if (collideWithEntity(entity))
    {
        collideEntity(jousterEntity);
    }
}

void JousterEntity::collideEntity(CollidingSpriteEntity* entity)
{
    if (entity != NULL) {} ;
}

void JousterEntity::collideEntityRight()
{
    if (speed >= 0) setSpeed(-1);
    else if (speed > -JOUSTER_NB_SPEED) setSpeed(speed - 1);
}

void JousterEntity::collideEntityLeft()
{
    if (speed <= 0) setSpeed(1);
    else if (speed < JOUSTER_NB_SPEED) setSpeed(speed + 1);
}

void JousterEntity::collideLava()
{

}

void JousterEntity::hitJump()
{
    if (velocity.y > GameConstants::getGameConstants()->JOUSTER_HIT_JUMP)
        velocity.y = GameConstants::getGameConstants()->JOUSTER_HIT_JUMP;
}

void JousterEntity::findFrame()
{
    switch (state)
    {
        case STATE_STANDING:
        {
            frame = 0;
            break;
        }
        /*case STATE_FALLING:
        {
            frame = 6;
            break;
        }
        case STATE_FLYING:
        {
            //if (velocity.y < -100.0f)
            if (jumpDelay >= JUMP_DELAY * 0.6f)
                frame = 8;
            //{
            //    if (jumpDelay >= JUMP_DELAY * 0.5f) frame = 6;
            //    else frame = 8;
            //}
            else
                frame = 7;
            break;
        }*/
        case STATE_FALLING: case STATE_FLYING:
        {
            float frameSpeed = speed * 0.04f;
            if (frameSpeed < 0.0f) frameSpeed = -frameSpeed;
            frameSpeed += 1.8f;

            if (spriteType == JousterEntity::SPRITE_HERO)
            {
                frame = 6 + (int)(age * frameSpeed * 8.0f) % 8;
                if (frame == 11) frame = 9;
                if (frame == 12) frame = 8;
                if (frame == 13) frame = 7;

                if (velocity.y > maxY * 0.75f) frame = 10;
            }
            else
            {
                frame = 6 + (int)(age * frameSpeed * 4.0f) % 4;
                if (frame == 9) frame = 7;

                if (velocity.y > maxY * 0.05f) frame = 8;
            }


            break;
        }
        case STATE_WALKING:
        {
            int oldFrame = frame;
            int frameSpeed = speed;
            if (frameSpeed < 0) frameSpeed = -frameSpeed;
            if (spriteType == JousterEntity::SPRITE_HERO)
            {
                frame = (int)(age * (float)frameSpeed * 4.0f) % 6;
                switch (frame)
                {
                    case 3: frame = 0; break;
                    case 4: frame = 3; break;
                    case 5: frame = 4; break;
                }
                if (frame != oldFrame && frame == 0)
                    LogicEngine::getLogicEngine()->playSound(SOUND_STEP);
            }
            else
            {
                frame = 1 + (int)(age * (float)frameSpeed * 4.0f) % 4;
                if (frame != oldFrame && frame % 2 == 0)
                    LogicEngine::getLogicEngine()->playSound(SOUND_STEP);
            }
            break;
        }
        case STATE_BRAKING:
        {
            frame = 5;
            LogicEngine::getLogicEngine()->setBraking(true);
            break;
        }
        case STATE_AIR_BRAKING:
        {
            if (spriteType == JousterEntity::SPRITE_HERO)
                frame = 11;
            else
                frame = 9;
            //LogicEngine::getLogicEngine()->setBraking(true);
            break;
        }
    }
}

bool JousterEntity::collidingWithLava()
{
    if (boundingBox.Bottom > (tileHeight - 2) * map->getHeight() + TILE_HEIGHT) return true;
    return false;
}

void JousterEntity::fallFromMount(bool generatesEgg)
{
    MountEntity* mountEntity = new MountEntity(image, spriteType, x, y);
    mountEntity->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);
    mountEntity->setLeftDirection (x - (float)offsetX < (float)(map->getWidth() * TILE_WIDTH / 2));
    mountEntity->setSpeed(speed);

    if (generatesEgg) return;
    FallingRiderEntity* fallingRiderEntity = new FallingRiderEntity(image, x, y);
    fallingRiderEntity->setVelocity(Vector2D(0, -80));
    fallingRiderEntity->setWeight(300);
    fallingRiderEntity->setMirror(velocity.x <= 0.0f);
}

void JousterEntity::fallInLava()
{
    BurningJousterEntity* entity = new BurningJousterEntity(image, x, y);
    entity->setMirror(velocity.x < 0.0f);
}
