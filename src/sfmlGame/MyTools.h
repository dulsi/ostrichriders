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

#ifndef __MYTOOLS
#define __MYTOOLS

#include <stdlib.h>
#include <math.h>

/** Vector utility, used in physics
 ** Default constructor creates a random Vector */
class Vector2D
{
public:
	float x, y;
	Vector2D(float amplitude = 1.0f)
	{
		float v = (float)rand() / (float)RAND_MAX;
		v *= 6.283f;
		x = cosf(v) * amplitude;
        y = sinf(v) * amplitude;
    }

	Vector2D(float m_x, float m_y) { x = m_x; y = m_y; }

	float distance2(Vector2D vector)
	{
	    return ( (vector.x - x) * (vector.x - x) + (vector.y - y) * (vector.y - y) );
	}

    float distance2(Vector2D vector, float repeatZone)
	{
	    float result = (vector.x - x) * (vector.x - x) + (vector.y - y) * (vector.y - y);

	    float d2 = (vector.x - ( x + repeatZone) ) * (vector.x - ( x + repeatZone)) + (vector.y - y) * (vector.y - y);
	    if (d2 < result) result = d2;

	    d2 = ( (vector.x + repeatZone) - x) * ((vector.x + repeatZone) - x) + (vector.y - y) * (vector.y - y);
	    if (d2 < result) result = d2;

	    return result;
	}
};

class IntCoord
{
public:
	int x, y;
    IntCoord(int x, int y) { this->x = x; this->y = y; }
};

#endif
