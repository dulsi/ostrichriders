
#include <iostream>

#include "joust/JoustGame.h"

using namespace std;


int main()
{
    JoustGame::initResources();

    JoustGame game;
    game.startGame();


    cout << "Thanks for playing !" << endl;
    return 0;
}
