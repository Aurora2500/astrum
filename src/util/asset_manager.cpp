#include <fstream>
#include <iostream>
#include <sstream>

#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "asset_manager.hpp"

AssetManager::AssetManager()
{
	// char *base = SDL_GetBasePath();
	m_base_path = "./";
	// SDL_free(base);
	m_shader_watcher.set_callback([this](std::string const &filename) {
		if (!filename.ends_with(".glsl"))
			return;
		std::string name = filename.substr(0, filename.find_last_of('.'));

		std::string path = m_base_path + "assets/shaders/" + filename;

		std::ifstream file(path);
		std::string src = (std::stringstream() << file.rdbuf()).str();

		auto it = m_shaders.find(name);
		if (it == m_shaders.end())
		{
			return;
		}
		std::cout << "Reloading shader: " << filename << std::endl;
		rendering::Shader new_shader(src);
		*it->second.get() = std::move(new_shader);
	});

	m_shader_watcher.add_watch(m_base_path + "assets/shaders");
}

rendering::Shader &AssetManager::get_shader(const std::string &name)
{
	// check if shader is already loaded
	auto it = m_shaders.find(name);
	if (it != m_shaders.end())
	{
		return *it->second;
	}
	// else, we load it
	std::string path = m_base_path + "assets/shaders/" + name + ".glsl";
	std::ifstream file(path);
	std::string src = (std::stringstream() << file.rdbuf()).str();
	m_shaders.insert({name, std::make_unique<rendering::Shader>(src)});
	return *m_shaders[name];
}

std::vector<uint8_t> AssetManager::load_image(const std::string &path, int &width, int &height, int &channels, bool flip)
{
	std::string full_path = m_base_path + "assets/textures/" + path;
	std::cout << "Loading image: " << full_path << std::endl;
	stbi_set_flip_vertically_on_load(flip);
	stbi_uc *data = stbi_load(full_path.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		std::cerr << "Failed to load image: " << full_path << std::endl;
		return {};
	}
	std::vector<uint8_t> image_data(data, data + width * height * channels);
	stbi_image_free(data);
	return image_data;
}

void AssetManager::poll()
{
	m_shader_watcher.poll();
}