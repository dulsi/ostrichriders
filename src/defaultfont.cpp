#include "defaultfont.h"

namespace OstrichRiders
{
    static sf::Font defFont;
    static bool init = true;

    sf::Font &GetDefaultFont()
    {
        if (init)
        {
            defFont.loadFromFile("/usr/share/fonts/liberation/LiberationSans-Regular.ttf");
            init = false;
        }
        return defFont;
    }
}
