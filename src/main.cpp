#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <getopt.h>

#include "joust/JoustGame.h"

using namespace std;

int dirExists(const char *path)
{
    struct stat info;

    if(stat(path, &info) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    char opt;
    static struct option long_options[] =
    {
        {0, 0, 0, 0}
    };
#ifdef __linux__
    if (!dirExists(GameConstants::JOUST_DATA_DIR.data()))
    {
        printf("Directory '%s' not found using './data'\n", GameConstants::JOUST_DATA_DIR.data());
        GameConstants::JOUST_DATA_DIR = "./data/";
    }
#endif
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
