#pragma once

#include <unordered_map>
#include <memory>
#include <vector>

#include "file_watch.hpp"
#include "rendering/shaders.hpp"
#include "text.hpp"
#include "rendering/texture.hpp"

class AssetManager
{
private:
	std::string m_base_path;
	std::unordered_map<std::string, std::unique_ptr<rendering::Shader>> m_shaders;
	std::unordered_map<std::string, std::shared_ptr<rendering::Cubemap>> m_cubemaps;
	FileWatcher m_shader_watcher;

	Text m_text;
	std::unordered_map<std::string, std::unique_ptr<FontFace>> m_fonts;
	

public:
	AssetManager();

	rendering::Shader &get_shader(const std::string &name);
	FontFace &get_font(const std::string &name);
	
	std::vector<uint8_t> load_image(const std::string &path, unsigned int &width, unsigned int &height);
	std::shared_ptr<rendering::Cubemap> get_cubemap(const std::string &name);
	void poll();
};