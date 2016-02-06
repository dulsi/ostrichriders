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

#ifndef FLYINGSCOREENTITY_CPP_INCLUDED
#define FLYINGSCOREENTITY_CPP_INCLUDED

#include <sstream>
#include <iostream>

#include "Constants.h"
#include "FlyingScoreEntity.h"
#include "../defaultfont.h"

FlyingScoreEntity::FlyingScoreEntity(float x, float y, int intText) : TextEntity(&OstrichRiders::GetDefaultFont(), 17, x, y)
{
    setText(intText);
    setWeight(-60);
    setAlignment(TextEntity::ALIGN_CENTER);
    setColor(TextEntity::COLOR_FADING_BLUE);
    setLifetime(2.0f);
}

FlyingScoreEntity::FlyingScoreEntity(float x, float y, int intText, int combo) : TextEntity(&OstrichRiders::GetDefaultFont(), 16 + combo, x, y)
{
    //std::string str = "(x";

    std::ostringstream intStream;
    intStream << "(x" << combo << ") " << intText;
    //str += intStream.str();

    //std::ostringstream comboStream;
    //comboStream << combo;
    //str += ") " + intStream.str();


    setText(intStream.str());

    setWeight(-60);
    setAlignment(TextEntity::ALIGN_CENTER);
    setColor(TextEntity::COLOR_FADING_BLUE);
    setLifetime(2.0f);
}

FlyingScoreEntity::FlyingScoreEntity(float x, float y, std::string text): TextEntity(&OstrichRiders::GetDefaultFont(), 18, x, y)
{
    setText(text);
    setWeight(-60);
    setAlignment(TextEntity::ALIGN_CENTER);
    setColor(TextEntity::COLOR_FADING_BLUE);
    setLifetime(2.0f);
}
#endif // FLYINGSCOREENTITY_CPP_INCLUDED
