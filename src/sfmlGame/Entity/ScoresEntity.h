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

#ifndef SCORESENTITY_H_INCLUDED
#define SCORESENTITY_H_INCLUDED

#include "GameEntity.h"
#include "../Model/GameScores.h"

// Basis class for text
class ScoresEntity : public GameEntity
{
public:
    // create a sprite with the entire image
    ScoresEntity(const sf::Font* font, int size, GameScores* gameScores, float x, float y, float xf, float dy);
    ~ScoresEntity();

    virtual void render(sf::RenderWindow* app);
	virtual void animate(float delay);


protected:
    int size;   // police's size
    sf::String* string;
    float xf;   // right limit
    float dy;   // intervale between two lines
    GameScores* gameScores;

    int rColor[2];
    int gColor[2];
    int bColor[2];
};

#endif // SCORESENTITY_H_INCLUDED
