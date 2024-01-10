#pragma once

#include <unordered_map>
#include <memory>
#include <vector>

#include "file_watch.hpp"
#include "rendering/shaders.hpp"
#include "text.hpp"

class AssetManager
{
private:
	std::string m_base_path;
	std::unordered_map<std::string, std::unique_ptr<rendering::Shader>> m_shaders;
	FileWatcher m_shader_watcher;

	Text m_text;
	std::unordered_map<std::string, std::unique_ptr<FontFace>> m_fonts;
	

public:
	AssetManager();

	rendering::Shader &get_shader(const std::string &name);
	FontFace &get_font(const std::string &name);
	
	std::vector<uint8_t> load_image(const std::string &path, int &width, int &height, int &channels, bool flip = true);
	void poll();
};