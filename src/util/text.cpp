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

FontFace Text::load_font(const std::string &path)
{
	FontFace face;
	FT_Error err = FT_New_Face(m_library, path.c_str(), 0, &face.m_face);
	if (err)
	{
		std::cerr << "Error loading font face." << std::endl;
	}
	return face;
}

FontFace::~FontFace()
{
	FT_Error err = FT_Done_Face(m_face);
	if (err)
	{
		std::cerr << "Error deinitializing FreeType face." << std::endl;
	}
}

void FontFace::set_size(int size)
{
	FT_Error err = FT_Set_Pixel_Sizes(m_face, 0, size);
	if (err)
	{
		std::cerr << "Error setting font size." << std::endl;
	}
}