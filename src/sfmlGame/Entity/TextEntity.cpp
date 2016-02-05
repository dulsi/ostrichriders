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

#include "TextEntity.h"

TextEntity::TextEntity(const sf::Font* font, int size, float x, float y) : GameEntity(x, y)
{
    string = new sf::String(L"", *font, (float)size);
    alignment = ALIGN_LEFT;
    colorType = COLOR_WHITE;
}

void TextEntity::render(sf::RenderWindow* app)
{
    align();
    applyColor();
    app->Draw(*string);
}

void TextEntity::animate(float delay)
{
    GameEntity::animate(delay);
}

void TextEntity::setText(std::wstring text)
{
    string->SetText(text);
}

void TextEntity::setText(std::string text)
{
    string->SetText(text);
}

void TextEntity::setText(int intText)
{
    std::ostringstream intStream;
    intStream << intText;
    string->SetText(intStream.str());
}

void TextEntity::setColor(int colorType)
{
    this->colorType = colorType;
}

void TextEntity::setAlignment(int alignment)
{
    this->alignment = alignment;
}

void TextEntity::align()
{
    switch (alignment)
    {
        case ALIGN_LEFT:
        string->SetPosition(x, y - string->GetRect().GetHeight() / 2);
        break;

        case ALIGN_CENTER:
        string->SetPosition( x - string->GetRect().GetWidth() / 2,
                             y - string->GetRect().GetHeight() / 2);
        break;

        case ALIGN_RIGHT:
        string->SetPosition( x - string->GetRect().GetWidth(),
                             y - string->GetRect().GetHeight() / 2);
        break;
    }
}

void TextEntity::applyColor()
{
    switch (colorType)
    {
        case COLOR_BLUE: string->SetColor(sf::Color(0, 0, 255, 255)); break;
        case COLOR_RED: string->SetColor(sf::Color(255, 0, 0, 255)); break;
        case COLOR_GREEN: string->SetColor(sf::Color(0, 255, 0, 255)); break;
        case COLOR_FADING_BLUE: string->SetColor(sf::Color(128, 128, 255, (sf::Uint8)(getFade() * 255))); break;
        case COLOR_FADING_WHITE: string->SetColor(sf::Color(255, 255, 255, (sf::Uint8)(getFade() * 255))); break;
        case COLOR_BLINKING_WHITE: string->SetColor(sf::Color(255, 255, 255, (sf::Uint8)((1.0f + cosf(age * 4.0f)) * 127.0f))); break;

        default: string->SetColor(sf::Color(255, 255, 255, 255)); break;
    }
}
