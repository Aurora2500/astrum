#include "text.hpp"

#include "util/locator.hpp"

namespace rendering
{

TextAtlas::TextAtlas()
{
	
}

void TextAtlas::load()
{
	m_glyphs.reserve(128);

	auto &assets = Locator::assets();

	auto &font = assets.get_font("arial");
}

}