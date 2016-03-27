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

#ifndef GAMESCORES_H_INCLUDED
#define GAMESCORES_H_INCLUDED

#include <string>
#include <vector>

using namespace std ;

/** Used to load, store and save High-Scores. */
class GameScores {

public:
    GameScores(const string &userDir, const string &dataDir, const string &fileName);

    void loadScores();
    void saveScores();

    void setFilename(const string &fileName);

    int getScore(int n);
    string getName(int n);
    void addScore(int score, std::string name);

    bool isNewScore(int n);
    void resetNewScores();

    //void reset();

protected:
    int scores[10];
    string names[10];
    vector<int> newScore;

    string userDir;
    string dataDir;
    string fileName;
};

#endif // GAMESCORES_H_INCLUDED
