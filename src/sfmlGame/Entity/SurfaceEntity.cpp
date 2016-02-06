/**  This file is part of sfmlGame.
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

#include "SurfaceEntity.h"

SurfaceEntity::SurfaceEntity(float x, float y, int width, int height, int fadeStyle) : GameEntity(x, y)
{
    this->image = image;
    this->fadeStyle = fadeStyle;
    image.create(1, 1, sf::Color(255, 255, 255, 255));
    imageTex.loadFromImage(image);
    sprite.setTexture(imageTex);
    setSize(width, height);
}

void SurfaceEntity::setSize(int width, int height)
{
    this->width  = width;
    this->height = height;
    sprite.setScale((float)width, (float)height);
}

void SurfaceEntity::render(sf::RenderWindow* app)
{
    sprite.setPosition(x, y);

    //if (isFading)
    {
        //sprite.SetColor(sf::Color(255, 255, 255, (sf::Uint8)(getFade() * 255)));
    }

    app->draw(sprite);
}

void SurfaceEntity::setColor(int r, int g, int b, int alpha)
{
    sprite.setColor(sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)alpha));
}

void SurfaceEntity::animate(float delay)
{
    GameEntity::animate(delay);
}
