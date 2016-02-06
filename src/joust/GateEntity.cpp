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

#include "GateEntity.h"
#include "Constants.h"

#include "../sfmlGame/MediaManagers/ImageManager.h"

GateEntity::GateEntity(float x, float y, int gateColor) : SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_GATE),
                                x, y, GATE_WIDTH, GATE_HEIGHT)
{
    //sprite
    lifetime = 1.0f;
    this->gateColor = gateColor;
}

GateEntity::~GateEntity()
{
}

void GateEntity::render(sf::RenderWindow* app)
{
    float fade = getFade();
    float part = fade > 0.5f ? 1.0f - fade : fade;

    sprite.setTextureRect(sf::IntRect(0, 0, width, (int)(2.0f * (float)height * part)));

    sprite.setPosition(x, y - (float)height * part * 2.0f + (float)height );
    sprite.setRotation(angle);
    int alpha = 180 + (int)(75.0f * cosf(age * 22.0f));
    if (gateColor == GATE_RED)
        sprite.setColor(sf::Color(255, 64, 64, (sf::Uint8)alpha));
    else
        sprite.setColor(sf::Color(64, 64, 255, (sf::Uint8)alpha));
    app->draw(sprite);
}

//void GateEntity::animate(float delay)
//{
//}
