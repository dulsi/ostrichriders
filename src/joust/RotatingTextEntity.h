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

#ifndef ROTATINGTEXTENTITY_H_INCLUDED
#define ROTATINGTEXTENTITY_H_INCLUDED

#include "Constants.h"
#include "../sfmlGame/Entity/TextEntity.h"

class RotatingTextEntity : public TextEntity
{
public:
    RotatingTextEntity(const sf::Font* font, int size, float x = 0.0f, float y = 0.0f);

    virtual void render(sf::RenderWindow* app);
	virtual void animate(float delay);

	virtual void setText(size_t index, std::string text);
	virtual void setText(size_t index, int intText);

protected:
    std::vector<std::string> texts;
    int current;
    float currentTime;
};

#endif // TEXTENTITY_H_INCLUDED
