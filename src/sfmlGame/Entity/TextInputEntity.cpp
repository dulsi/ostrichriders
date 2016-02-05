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

#include "TextInputEntity.h"

TextInputEntity::TextInputEntity(const sf::Font* font, int size, float x, float y) : GuiEntity(x, y)
{
    string = new sf::String(L"", *font, (float)size);
    inputText = "";
    preText = "";
    alignment = ALIGN_LEFT;
    colorType = COLOR_WHITE;
    sizeMax = 32;
    isReturned = false;
}

std::string TextInputEntity::getInputText() { return inputText; }
bool TextInputEntity::getReturned() { return isReturned; }
void TextInputEntity::setInputText(std::string inputText) { this->inputText = inputText; }
void TextInputEntity::setPreText(std::string preText) { this->preText = preText; }
void TextInputEntity::setSizeMax(unsigned int sizeMax) { this->sizeMax = sizeMax; }

void TextInputEntity::render(sf::RenderWindow* app)
{
    if (((int)(age * 2.0f)) % 2 == 0)
        string->SetText(preText + inputText + "_");
    else
        string->SetText(preText + inputText);

    align();
    applyColor();
    app->Draw(*string);
}

void TextInputEntity::animate(float delay)
{
    GameEntity::animate(delay);
}

void TextInputEntity::onEvent(sf::Event event)
{
    if (!isActive || age < 0.8f) return;

    if (event.Type == sf::Event::KeyPressed) {
        if (event.Key.Code == sf::Key::Return)
        {
            isReturned = true;
        }
        else if (event.Key.Code == sf::Key::Back)
        {
            if (inputText.size() > 0) inputText.erase(inputText.size()-1);
        }
        else if (event.Key.Code >= sf::Key::A && event.Key.Code <= sf::Key::Z)
        {
            if (inputText.size() <= +sizeMax)
                inputText += ('A' + (event.Key.Code - sf::Key::A));
        }
        else if (event.Key.Code >= sf::Key::Num0 && event.Key.Code <= sf::Key::Num9)
        {
            if (inputText.size() <= +sizeMax)
                inputText += ('0' + (event.Key.Code - sf::Key::Num0));
        }
    }
}

void TextInputEntity::setColor(int colorType)
{
    this->colorType = colorType;
}

void TextInputEntity::setAlignment(int alignment)
{
    this->alignment = alignment;
}

void TextInputEntity::align()
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

void TextInputEntity::applyColor()
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
