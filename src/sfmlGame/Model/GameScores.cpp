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

#include "GameScores.h"

#include <fstream>

GameScores::GameScores(char* fileName)
{
    this->fileName = fileName;
    loadScores();
    resetNewScores();
}


//void GameScores::reset(const char* initialFileName)
//{
//    loadScores(initialFileName);
//    saveScores();
//}

void GameScores::loadScores()
{
    //const char* fileName="data/scores.dat";
    printf ("Loading %s...\n", fileName);
    ifstream f(fileName);
    if (!f.is_open())
    {
        printf ("[ERROR] Cannot open %s\n", fileName);
        return;
    }

    int n;
    int i;
	char c[64];

    for (i = 0; i < 10; i++)
    {
        f >> n;
        scores[i] = n;

        f >> c;
        names[i] = c;
    }

    f.close();
}

void GameScores::saveScores()
{
    ofstream f(fileName);
    if (!f.is_open()) return;

    int i;

    for (i = 0; i < 10; i++)
    {
        f << scores[i] << " " << names[i] << endl;
    }

    f.close();
}

int GameScores::getScore(int n) { return scores[n]; }
string GameScores::getName(int n) { return names[n]; }

void GameScores::setFilename(char* fileName)
{
    this->fileName = fileName;
    loadScores();
    resetNewScores();
}

void GameScores::addScore(int score, string name)
{
    if (name.size() < 1) name = "ANONYMOUS";
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        if (score > scores[i]) break;
    }
    for (int j = 9; j > i; j--)
    {
        scores[j] = scores[j - 1];
        names[j] = names[j - 1];
    }
    scores[i] = score;
    names[i] = name;

    saveScores();

    if (newScore1 == -1)
    {
        newScore1 = i;
    }
    else if (newScore2 == -1)
    {
        newScore2 = i;
        if (newScore2 < newScore1) newScore1++;
    }
}

bool GameScores::isNewScore(int n)
{
    return (newScore1 == n || newScore2 == n);
}

void GameScores::resetNewScores()
{
    newScore1 = -1;
    newScore2 = -1;
}
