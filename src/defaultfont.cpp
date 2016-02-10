#include "defaultfont.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#define JOUST_FONT  "/usr/share/fonts/liberation/LiberationSans-Regular.ttf"
#else
#define JOUST_FONT  "./data/LiberationSans-Regular.ttf"
#endif

namespace OstrichRiders
{
    static sf::Font defFont;
    static bool init = true;

    sf::Font &GetDefaultFont()
    {
        if (init)
        {
            bool success = defFont.loadFromFile("/usr/share/fonts/liberation/LiberationSans-Regular.ttf");
            if (!success)
            {
                printf("Failed to load font %s\n", JOUST_FONT);
                exit(1);
            }
            init = false;
        }
        return defFont;
    }
}
