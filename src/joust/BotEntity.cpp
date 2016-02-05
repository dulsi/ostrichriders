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

#include "BotEntity.h"
#include "Constants.h"
#include "LogicEngine.h"
#include "EggEntity.h"
#include "PlayerEntity.h"
#include "FlyingScoreEntity.h"
#include "../sfmlGame/MediaManagers/ImageManager.h"

BotEntity::BotEntity(sf::Image* image, float x, float y, int aiType)
                                                    : JousterEntity(image, JousterEntity::SPRITE_ENNEMY, x, y)
{
    this->aiType = aiType;
    //printf("AI %d created\n", aiType);
    botJumpDelay = 0.8f + (float)rand() / (float)RAND_MAX * 0.5f;
    isLeftDirection = rand() % 2 == 0;

    aiPsy = rand() % 3;
    psySpeed = 1 + rand() % 4;
    psyDelay = 3.0f + (float)rand() / (float)RAND_MAX * 5.0f;
    wannaTurn = 0;
}

BotEntity::~BotEntity()
{
    //printf("AI %d destroyed\n", aiType);
}

void BotEntity::render(sf::RenderWindow* app)
{
    if (age < JOUSTER_LATENCY / 2)
        return;
    else if (age < JOUSTER_LATENCY)
        sprite.SetColor(sf::Color(255, 255, 255, (sf::Uint8)(200.0f * age)));
    else // TODO
        sprite.SetColor(sf::Color(255, 255, 255, 255 ));
    JousterEntity::render(app);
}

int BotEntity::getAiType()
{
    return aiType;
}

void BotEntity::animate(float delay)
{
    if (age < JOUSTER_LATENCY)
    {
        age += delay;
        return;
    }

    if (velocity.x > 0.1f) isLeftDirection = false;
    else if (velocity.x < -0.1f) isLeftDirection = true;

    bool speedOK = false;
    if (isLeftDirection && speed == -psySpeed) speedOK = true;
    else if (!isLeftDirection && speed == psySpeed) speedOK = true;

    if (isLeftDirection && speed < -psySpeed) isLeftDirection = false;
    if (!isLeftDirection && speed > psySpeed) isLeftDirection = true;

    if (wannaTurn > 0 && isLeftDirection)
    {
        speedOK = false;
        isLeftDirection = false;
    }
    else if (wannaTurn < 0 && !isLeftDirection)
    {
        speedOK = false;
        isLeftDirection = true;
    }
    else (wannaTurn = 0);


    botJumpDelay -= delay;

    wannaJump = false;
    if (botJumpDelay <= 0.0f)
    {
        wannaJump = true;
        if (aiPsy == 0)
            botJumpDelay = 0.3f + (float)rand() / (float)RAND_MAX * 0.5f;
        else if (aiPsy == 1)
            botJumpDelay = 0.6f + (float)rand() / (float)RAND_MAX * 0.8f;
        else if (aiPsy == 2)
            botJumpDelay = 30.0f;
    }

    psyDelay-= delay;
    if (psyDelay <= 0.0f)
    {
        aiPsy = rand() % 3;
        psySpeed = 3 + rand() % 3;
        psyDelay = 2.0f + (float)rand() / (float)RAND_MAX * 4.0f;
        if (botJumpDelay > 0.3f)
        {
            if (aiPsy == 0)
                botJumpDelay = 0.3f + (float)rand() / (float)RAND_MAX * 0.5f;
            else if (aiPsy == 1)
                botJumpDelay = 0.6f + (float)rand() / (float)RAND_MAX * 0.8f;
            else if (aiPsy == 2)
                botJumpDelay = 30.0f;
        }
        if (rand() % 2 == 0)
        {
            if (speed != 0) wannaTurn = -speed;
        }
    }

    // avoiding lava
    if ((float)(boundingBox.Bottom) > (float)(tileHeight - 2) * (float)(map->getHeight()) + 5.0f) wannaJump = true;

    if (aiType == 1) repulse(40000.0f);
    if (aiType == 2) repulse(60000.0f);
    if (aiType == 3) repulse(80000.0f);

    wannaGoRight = false;
    wannaGoLeft = false;

    if (!speedOK && isLeftDirection)
    {
        wannaGoLeft = true;
    }
    else if (!speedOK)
    {
        wannaGoRight = true;
    }


    JousterEntity::animate(delay);
}

void BotEntity::onDying()
{
    fallFromMount(true);

    EggEntity* eggEntity = new EggEntity(ImageManager::getImageManager()->getImage(IMAGE_EGG), x, y);
    eggEntity->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);
    eggEntity->setVelocity(Vector2D(velocity.x, velocity.y));
    if (aiType == N_BOTS - 1)
        eggEntity->setEggType(aiType);
    else
        eggEntity->setEggType(aiType + 1);
}

void BotEntity::collideEntity(CollidingSpriteEntity* entity)
{
    JousterEntity* jousterEntity = dynamic_cast<JousterEntity*>(entity);
    BotEntity* botEntity = dynamic_cast<BotEntity*>(entity);
    PlayerEntity* playerEntity = dynamic_cast<PlayerEntity*>(entity);
    if (botEntity != NULL || playerEntity != NULL)
    {
        LogicEngine::getLogicEngine()->playSound(SOUND_COLLISION_WITH_JOUSTER);
        if (playerEntity != NULL)
        {
            if (age > JOUSTER_LATENCY * 2 && entity->getAge() > JOUSTER_LATENCY * 2)
            {
                if (y >= entity->getY() + JOUSTER_KILLING_DISTANCE)
                {
                    isDying = true;
                    jousterEntity->hitJump();
                    //new FlyingScoreEntity(x, y, BOT_SCORE[aiType]);
                    LogicEngine::getLogicEngine()->onTargetDying(this, playerEntity->getPlayerNumber());
                    LogicEngine::getLogicEngine()->playSound(SOUND_JOUSTER_FALL);
                    return;
                }
                if (y <= entity->getY() - JOUSTER_KILLING_DISTANCE)
                {
                    entity->setDying(true);
                    ((PlayerEntity*)entity)->fallFromMount();
                    LogicEngine::getLogicEngine()->onPlayerDying(playerEntity->getPlayerNumber(), -1);
                    hitJump();
                    LogicEngine::getLogicEngine()->playSound(SOUND_JOUSTER_FALL);
                    return;
                }
            }
            if (x < entity->getX())
            {
                collideEntityRight();
                jousterEntity->collideEntityLeft();

                x = (float)((int)x);
                while (!collideWithEntity(entity))
                {
                    x--;
                }
            }
        }

        if (x > entity->getX())
        {
            collideEntityLeft();
            jousterEntity->collideEntityRight();

            x = (float)((int)x);
            while (!collideWithEntity(entity))
            {
                x++;
            }

        }
    }
}

bool BotEntity::repulse(float maxDist2)
{
    sprite.SetColor(sf::Color(255, 255 ,255, 255));

    // find the closest player
    int closestPlayer = -1;
    float dist2 = 10000000.0f;
    for (int i = 0; i < LogicEngine::getLogicEngine()->getNPlayers(); i++)
    {
        //float dist2 = (x - playerEntity->getX()) * (y - playerEntity->getY());
        if (LogicEngine::getLogicEngine()->getPlayerStatus(i) == LogicEngine::PLAYER_STATUS_PLAYING)
        {
            PlayerEntity* playerEntity = LogicEngine::getLogicEngine()->getPlayerEntity(i);
            float currDist2 = Vector2D(x, y).distance2(Vector2D(playerEntity->getX(), playerEntity->getY()), CLIENT_WIDTH);

            if (currDist2 < dist2 && currDist2 < maxDist2)
            {
                closestPlayer = i;
                dist2 = currDist2;
            }
        }
    }
    if (closestPlayer < 0) return false;


    PlayerEntity* playerEntity = LogicEngine::getLogicEngine()->getPlayerEntity(closestPlayer);

    int xPlayer = (int)(playerEntity->getX());
    int yPlayer = (int)(playerEntity->getY());

    if (xPlayer < (int)x && ((int)x - xPlayer) > CLIENT_WIDTH / 2) xPlayer += CLIENT_WIDTH;
    if (xPlayer > (int)x && (xPlayer - (int)x) > CLIENT_WIDTH / 2) xPlayer -= CLIENT_WIDTH;

    if (yPlayer < y)
    {
        sprite.SetColor(sf::Color(255, 122 ,122, 255));
        if (xPlayer >= x/* && playerEntity->getVelocity().x < 0.0f*/)
        {
            if (dist2 >= JOUSTER_WIDTH * JOUSTER_WIDTH)
            {
                wannaJump = true;
            }
            else
            {
                isLeftDirection = true;
                psySpeed = 5;
            }
        }
        else if (xPlayer <= x/* && playerEntity->getVelocity().x > 0.0f*/)
        {
            if (dist2 >= JOUSTER_WIDTH * JOUSTER_WIDTH)
            {
                wannaJump = true;
            }
            else
            {
                isLeftDirection = false;
                psySpeed = 5;
            }
        }
    }
    else
    {
        sprite.SetColor(sf::Color(122, 122 ,255, 255));
        if (xPlayer > x/* && playerEntity->getVelocity().x < 0.0f*/)
        {
            isLeftDirection = false;
            psySpeed = 5;
        }
        else if (xPlayer < x/* && playerEntity->getVelocity().x > 0.0f*/)
        {
            isLeftDirection = true;
            psySpeed = 5;
        }
    }
    return false;
}

void BotEntity::collideLava()
{
    setDying(true);
    LogicEngine::getLogicEngine()->onTargetDying(this, -1);
}
