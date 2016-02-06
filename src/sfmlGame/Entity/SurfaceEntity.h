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

#ifndef SURFACEENTITY_H_INCLUDED
#define SURFACEENTITY_H_INCLUDED

#include "GameEntity.h"

// Basis class for sprite
class SurfaceEntity : public GameEntity
{
public:
    SurfaceEntity(float x, float y, int width, int height, int fadeStyle = FADE_NONE);

    virtual void render(sf::RenderWindow* app);
	virtual void animate(float delay);

	void setColor(int r, int g, int b, int alpha = 255);
	void setSize(int width, int height);

	enum FadeStyleEnum { FADE_NONE, FADE_IN, FADE_OUT };

protected:
    sf::Sprite sprite;
    sf::Image image;
    sf::Texture imageTex;
    int width;
    int height;
    int fadeStyle;
};

#endif // SURFACEENTITY_H_INCLUDED
