#pragma once

#include <unordered_map>
#include <memory>

#include "rendering/shaders.hpp"

class AssetManager
{
private:
	std::string m_base_path;
	std::unordered_map<std::string, std::unique_ptr<rendering::Shader>> m_shaders;

public:
	AssetManager();
	rendering::Shader &get_shader(const std::string &name);
};