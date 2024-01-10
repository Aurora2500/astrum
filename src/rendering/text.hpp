#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "texture.hpp"

namespace rendering
{

struct Glyph
{
	glm::uvec2 size;
	glm::uvec2 bearing;
	int advance;
};


class TextAtlas
{
private:
	Texture m_texture;
	std::unordered_map<char, Glyph> m_glyphs;

public:
	TextAtlas();

	void load();

	void draw_text(std::string const&text, float x, float y, float scale, glm::vec3 const&color);
};

}