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

#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>

class ImageManager
{
public:
    static ImageManager* getImageManager();
    void addImage(const char* fileName);
    bool reloadImage(int n, const char* fileName);
    sf::Texture* getImage(int n);

private:
    ImageManager();
    ~ImageManager();

    std::vector<sf::Texture*> textureArray;
};

#endif // IMAGEMANAGER_H_INCLUDED
