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

#include "SelectorEntity.h"
#include "Constants.h"

SelectorEntity::SelectorEntity(sf::Texture* image, float x, float y, int selected)
                                    : SpriteEntity(image, x, y, JOUSTER_WIDTH, JOUSTER_HEIGHT)
{
    this->selected = selected;
    sprite.setPosition(sprite.getPosition().x, y - 100.0f);
}

int SelectorEntity::getSelected() { return selected; }
void SelectorEntity::setSelected(int selected) { this->selected = selected; }

void SelectorEntity::render(sf::RenderWindow* app)
{
    sprite.setTextureRect(sf::IntRect(400, 0, 200, 200));
    if (selected == 0) sprite.setPosition(x - 250.0f, sprite.getPosition().y);
    else sprite.setPosition(x + 50.0f, sprite.getPosition().y);
    app->draw(sprite);

    sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    sprite.setPosition(x - 250.0f, sprite.getPosition().y);
    app->draw(sprite);

    sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
    sprite.setPosition(x + 50.0f, sprite.getPosition().y);
    app->draw(sprite);
}
