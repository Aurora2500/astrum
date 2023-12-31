#include <ft2build.h>
#include FT_FREETYPE_H

class Text
{
private:
	FT_Library m_library;

public:
	Text();
	~Text();
};