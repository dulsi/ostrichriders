
#include <iostream>
#include <getopt.h>

#include "joust/JoustGame.h"

using namespace std;

int main(int argc, char *argv[])
{
    char opt;
    static struct option long_options[] =
    {
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc,argv,"l:", long_options, NULL)) != EOF)
    {
        switch (opt)
        {
        case 'l':
            if (optarg)
            {
                string libDir = optarg;
                if ((libDir.length() > 0) && (libDir[libDir.length() - 1] != '/'))
                {
                    libDir += '/';
                }
                GameConstants::JOUST_DATA_DIR = libDir;
            }
            break;
        default:
            break;
        }
    }
    JoustGame::initResources(GameConstants::JOUST_DATA_DIR);

    JoustGame game;
    game.startGame();


    cout << "Thanks for playing !" << endl;
    return 0;
}
