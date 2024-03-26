#include "asset_manager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include <SDL2/SDL.h>
#include <stb/stb_image.h>
#include <lodepng.h>

#include "rendering/primitive/texture.hpp"

AssetManager::AssetManager()
{
	char *base = SDL_GetBasePath();
	m_base_path = base;
	SDL_free(base);
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

FontFace &AssetManager::get_font(const std::string &name)
{
	auto it = m_fonts.find(name);
	if (it != m_fonts.end())
	{
		return *it->second;
	}
	std::string path = m_base_path + "assets/fonts/" + name + ".ttf";
	m_fonts.insert({name, std::make_unique<FontFace>(m_text.load_font(path))});
	return *m_fonts[name];
}

std::vector<uint8_t> AssetManager::load_image(const std::string &path, unsigned int &width, unsigned int &height)
{
	std::string full_path = m_base_path + "assets/textures/" + path;
	std::cout << "Loading image: " << full_path << std::endl;
	std::vector<uint8_t> image_data;
	lodepng::decode(image_data, width, height, full_path, LCT_RGB);
	
	return image_data;
}

std::shared_ptr<rendering::Cubemap> AssetManager::get_cubemap(const std::string &name)
{
	auto it = m_cubemaps.find(name);
	if (it != m_cubemaps.end())
	{
		return it->second;
	}

	std::array<std::string, 6> faces = {
		"px.png",
		"nx.png",
		"py.png",
		"ny.png",
		"pz.png",
		"nz.png",
	};
	std::array<rendering::FaceData, 6> face_data;
	std::array<std::thread, 6> threads;
	for (int i = 0; i < 6; i++)
	{
		auto full_name = name + + "_" + faces[i];
		auto data = &face_data[i];
		threads[i] = std::thread([this, data, full_name]() {
			data->channels = 3;
			data->data = load_image(full_name, data->width, data->height);
		});
	}
	for (auto &t: threads)
		t.join();

	auto cubemap = std::make_shared<rendering::Cubemap>();
	cubemap->load(face_data);
	m_cubemaps.insert({name, cubemap});
	return cubemap;
}

void AssetManager::poll()
{
	m_shader_watcher.poll();
}