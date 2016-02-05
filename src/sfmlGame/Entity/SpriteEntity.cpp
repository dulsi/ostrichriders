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

#include "SpriteEntity.h"

SpriteEntity::SpriteEntity(sf::Image* image, float x, float y, int width, int height, int imagesProLine) : GameEntity(x, y)
{
    frame = 0;
    isFading = false;
    this->image = image;
    sprite.SetImage(*image);
    this->width  = width  <= 0 ? image->GetWidth()  : width;
    this->height = height <= 0 ? image->GetHeight() : height;
    //sprite.SetSubRect(sf::IntRect(0, 0, this->width, this->height));
    sprite.SetCenter((float)(this->width / 2), (float)(this->height / 2));
    this->imagesProLine = imagesProLine;
}

void SpriteEntity::setFading(bool isFading)
{
    this->isFading = isFading;
}

void SpriteEntity::setFrame(int frame) { this->frame = frame; }

void SpriteEntity::render(sf::RenderWindow* app)
{
    int nx = frame;
    int ny = 0;

    if (imagesProLine > 0)
    {
        nx = frame % imagesProLine;
        ny = frame / imagesProLine;
    }

    sprite.SetSubRect(sf::IntRect(nx * width, ny * height, (nx + 1) * width, (ny + 1) * height));

    sprite.SetX(x);
    sprite.SetY(y);
    sprite.SetRotation(angle);

    if (isFading)
    {
        sprite.SetColor(sf::Color(255, 255, 255, (sf::Uint8)(getFade() * 255)));
    }

    app->Draw(sprite);
}

void SpriteEntity::animate(float delay)
{
    GameEntity::animate(delay);
}
