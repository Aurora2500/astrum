#include "text.hpp"

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

Text::Text()
{
	FT_Error err = FT_Init_FreeType(&m_library);
	if (err)
	{
		std::cerr << "Error initializing FreeType library." << std::endl;
	}
}


Text::~Text()
{
	FT_Error err = FT_Done_FreeType(m_library);
	if (err)
	{
		std::cerr << "Error deinitializing FreeType library." << std::endl;
	}
}