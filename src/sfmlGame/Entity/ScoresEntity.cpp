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

#include <sstream>
#include <iostream>

#include "ScoresEntity.h"

ScoresEntity::ScoresEntity(const sf::Font* font, int size, GameScores* gameScores, float x, float y, float xf, float dy) : GameEntity(x, y)
{
    this->xf = xf;
    this->dy = dy;
    string = new sf::String(L"", *font, (float)size);
    this->gameScores = gameScores;

    rColor[0] = 255;
    gColor[0] = 80;
    bColor[0] = 80;

    rColor[1] = 255;
    gColor[1] = 255;
    bColor[1] = 120;
}

ScoresEntity::~ScoresEntity()
{
    delete string;
}

void ScoresEntity::render(sf::RenderWindow* app)
{
    for (int i = 0; i < 10; i++)
    {
        // moving color for new scores
        if (gameScores->isNewScore(i))
        {
            string->SetColor(sf::Color(sf::Uint8(100.f + sinf(age * 3.f) * 100.f),
                                       sf::Uint8(100.f + sinf(age * 4.f) * 100.f),
                                       sf::Uint8(100.f + cosf(age * 5.f) * 100.f)));
        }
        else
        {
            int c = i % 2;
            string->SetColor(sf::Color(sf::Uint8(rColor[c]),
                                       sf::Uint8(gColor[c]),
                                       sf::Uint8(bColor[c])));
        }

        string->SetX(x);
        string->SetY(y + i * dy);
        string->SetText(gameScores->getName(i));
        app->Draw(*string);

        std::ostringstream intStream;
        intStream << gameScores->getScore(i);
        string->SetText(intStream.str());
        string->SetX(xf - string->GetRect().GetWidth());
        app->Draw(*string);
    }
}

void ScoresEntity::animate(float delay)
{
    GameEntity::animate(delay);
}
