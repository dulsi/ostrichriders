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

#ifndef TEXTENTITY_H_INCLUDED
#define TEXTENTITY_H_INCLUDED

#include "GameEntity.h"

// Basis class for text
class TextEntity : public GameEntity
{
public:
    // create a sprite with the entire image
    TextEntity(const sf::Font* font, int size, float x = 0.0f, float y = 0.0f);

    virtual void render(sf::RenderWindow* app);
	virtual void animate(float delay);

	virtual void setText(std::wstring text);
	virtual void setText(std::string text);
	virtual void setText(int intText);

	void setAlignment(int alignment);
	void setColor(int colorType);
	enum alignmentEnum { ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER };
	enum colorTypeEnum { COLOR_WHITE,
                         COLOR_BLUE,
                         COLOR_RED,
                         COLOR_GREEN,
                         COLOR_FADING_WHITE,
                         COLOR_FADING_BLUE,
                         COLOR_BLINKING_WHITE };

protected:
    sf::Text* string;
    int size;
    int alignment;
    int colorType;

    void align();
    void applyColor();
};

#endif // TEXTENTITY_H_INCLUDED
