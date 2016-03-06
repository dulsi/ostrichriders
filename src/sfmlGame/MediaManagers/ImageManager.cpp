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

#include "ImageManager.h"
#include <stdio.h>

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
    printf("Releasing video memory...\n");
    for (unsigned int i = 0; i < textureArray.size(); i++)
    {
        delete(textureArray[i]);
    }
    textureArray.clear();
}

 ImageManager* ImageManager::getImageManager()
 {
   static ImageManager singleton;
   return &singleton;
 }

void ImageManager::addImage(const char* fileName)
{
    sf::Texture* newTexture = new sf::Texture;
    newTexture->loadFromFile(fileName);
    textureArray.push_back(newTexture);
}

bool ImageManager::reloadImage(int n, const char* fileName)
{
    return textureArray[n]->loadFromFile(fileName);
}

sf::Texture* ImageManager::getImage(int n)
{
    return textureArray[n];
}
