#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "texture.hpp"

namespace rendering
{

struct Glyph
{
	glm::uvec2 pos;
	glm::uvec2 size;
	glm::uvec2 bearing;
	int advance;
};


class TextAtlas
{
private:
	Texture m_texture;
	unsigned int m_width, m_height;
	std::unordered_map<char, Glyph> m_glyphs;

public:
	TextAtlas();

	void load();

	inline Texture& texture() { return m_texture; }
	
	void draw_text(std::string const&text, float x, float y, float scale);
};

}