#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>

#include "asset_manager.hpp"

AssetManager::AssetManager()
{
	// char *base = SDL_GetBasePath();
	m_base_path = "./";
	// SDL_free(base);
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
	m_shaders.insert({name, std::make_unique<rendering::Shader>(file)});
	return *m_shaders[name];
}