#include "defaultfont.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__
#include <fontconfig/fontconfig.h>
#endif

#ifdef __linux__
#define JOUST_FONT  OstrichRiders::FindDefaultFont().data()
#else
#define JOUST_FONT  "./data/LiberationSans-Regular.ttf"
#endif

namespace OstrichRiders
{
	static sf::Font defFont;
	static bool init = true;

#ifdef __linux__
	std::string FindDefaultFont()
	{
		std::string answer("/usr/share/fonts/liberation/LiberationSans-Regular.ttf");
		FcFontSet	*fs;
		FcPattern   *pat;
		FcResult	result;
		if (!FcInit())
		{
			return answer;
		}
		pat = FcNameParse((FcChar8 *)"LiberationSans-Regular.ttf");
		FcConfigSubstitute(0, pat, FcMatchPattern);
		FcDefaultSubstitute(pat);

		fs = FcFontSetCreate();
		FcPattern   *match;
		match = FcFontMatch(0, pat, &result);
		if (match)
		{
			FcChar8 *file;
			if (FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch)
			{
				answer = (const char *)file;
			}
			FcPatternDestroy(match);
		}
		FcPatternDestroy(pat);
		FcFini();
		return answer;
	}
#endif

	sf::Font &GetDefaultFont()
	{
		if (init)
		{
			bool success = defFont.loadFromFile(JOUST_FONT);
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
