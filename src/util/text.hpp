#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

class FontFace;

class Text
{
private:
	FT_Library m_library;

public:
	Text();
	~Text();

	FontFace load_font(const std::string &path);
};

class FontFace
{
private:
	FT_Face m_face;
	FontFace() = default;

public:
	~FontFace();

	void set_size(int size);


	friend class Text;
};