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

#include "PlayerEntity.h"
#include "Constants.h"
#include "LogicEngine.h"
#include "EggEntity.h"
#include "FlyingScoreEntity.h"
#include "../sfmlGame/MediaManagers/ImageManager.h"

PlayerEntity::PlayerEntity(sf::Texture* image, float x, float y, int playerNumber)
                                                    : JousterEntity(image, JousterEntity::SPRITE_HERO, x, y)
{
    this->playerNumber = playerNumber;
    //printf("Player %d created\n", playerNumber);
}

PlayerEntity::~PlayerEntity()
{
    //printf("Player %d destroyed\n", playerNumber);
}

int PlayerEntity::getPlayerNumber()
{
    return playerNumber;
}

void PlayerEntity::setPlayerInput(PlayerInput* playerInput)
{
    input = playerInput;
}


void PlayerEntity::render(sf::RenderWindow* app)
{
    if (age < JOUSTER_LATENCY / 2)
        return;
    else if (age < JOUSTER_LATENCY)
        sprite.setColor(sf::Color(255, 255, 255, sf::Uint8(200.0f * age)));
    else
        sprite.setColor(sf::Color(255, 255, 255, 255 ));
    JousterEntity::render(app);
}

void PlayerEntity::animate(float delay)
{
    if (age < JOUSTER_LATENCY)
    {
        age += delay;
        return;
    }
    // test input
    if (input->jump)
    {
        velocity.y = GameConstants::getGameConstants()->JOUSTER_JUMP;
        weight = GameConstants::getGameConstants()->JOUSTER_WEIGHT;
    }
    wannaJump = input->jump;

    wannaGoLeft = false;
    wannaGoRight = false;
    if (input->right)
        wannaGoRight = true;
    else if (input->left)
        wannaGoLeft = true;

    JousterEntity::animate(delay);
}

void PlayerEntity::onDying()
{

}

void PlayerEntity::readCollidingEntity(CollidingSpriteEntity* entity)
{
    EggEntity* eggEntity = dynamic_cast<EggEntity*>(entity);
    JousterEntity* jousterEntity = dynamic_cast<JousterEntity*>(entity);
    if (jousterEntity == NULL && eggEntity == NULL) return;
    if (jousterEntity != NULL && jousterEntity == this) return;

    if (collideWithEntity(entity))
    {
        collideEntity(entity);
    }
}

void PlayerEntity::collideEntity(CollidingSpriteEntity* entity)
{
    EggEntity* eggEntity = dynamic_cast<EggEntity*>(entity);
    if (eggEntity != NULL && entity->getAge() > 0.5f)
    {
        entity->setDying(true);
        LogicEngine::getLogicEngine()->onRemoveEgg(eggEntity->getEggType(), playerNumber);

        new FlyingScoreEntity(eggEntity->getX(), eggEntity->getY(), EGG_SCORE[eggEntity->getEggType()]);

        for (int i=0; i < 4; i++)
        {
            SpriteEntity* eggPart = new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_EGG),
                                                    eggEntity->getX(), eggEntity->getY(),
                                                    EGG_WIDTH / 2, EGG_HEIGHT / 2);
            eggPart->setVelocity(Vector2D (-30.0f + (float)rand() / (float)RAND_MAX * 60.0f,
                                            -30.0f + (float)rand() / (float)RAND_MAX * 60.0f));
            eggPart->setAngle((float)i * 90.0f);
            eggPart->setSpin(-300.0f + (float)rand() / (float)RAND_MAX * 600.0f);
            eggPart->setWeight(80.0f);
            eggPart->setLifetime(1.0f);
            eggPart->setFading(true);
        }
    }
    JousterEntity* jousterEntity = dynamic_cast<JousterEntity*>(entity);
    PlayerEntity* playerEntity = dynamic_cast<PlayerEntity*>(entity);
    if (playerEntity != NULL)
    {
        LogicEngine::getLogicEngine()->playSound(SOUND_COLLISION_WITH_JOUSTER);
        if (age > JOUSTER_LATENCY * 2 && entity->getAge() > JOUSTER_LATENCY * 2)
        {
            if (y >= entity->getY() + JOUSTER_KILLING_DISTANCE)
            {
                isDying = true;
                fallFromMount();
                LogicEngine::getLogicEngine()->onPlayerDying(playerNumber, playerEntity->getPlayerNumber());
                jousterEntity->hitJump();
                new FlyingScoreEntity(x, y, HUMAN_SCORE);
                LogicEngine::getLogicEngine()->playSound(SOUND_JOUSTER_FALL);
                return;
            }
            if (y <= entity->getY() - JOUSTER_KILLING_DISTANCE)
            {
                entity->setDying(true);
                playerEntity->fallFromMount();
                LogicEngine::getLogicEngine()->onPlayerDying(playerEntity->getPlayerNumber(), playerNumber);
                hitJump();
                new FlyingScoreEntity(entity->getX(), entity->getY(), HUMAN_SCORE);
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
        return;
    }
}

void PlayerEntity::collideLava()
{
    setDying(true);
    LogicEngine::getLogicEngine()->onPlayerDying(playerNumber, -1);

    fallInLava();
    for (int i = 0; i < 16; i++)
    {
        SpriteEntity* part = new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_BLACK_PART), x, (float)(boundingBox.top + boundingBox.height - 5));
        part->setLifetime(1.0f);
        part->setFading(true);
        part->setVelocity(Vector2D(-30.0f + (float)rand() / (float)RAND_MAX * 60.0f,
                                        -30.0f + (float)rand() / (float)RAND_MAX * 60.0f));
        part->setWeight(-40.0f);
    }
}
