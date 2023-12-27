#include <unordered_map>
#include <memory>

#include "shaders.hpp"

class AssetManager
{
private:
	std::string m_base_path;
	std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;

public:
	AssetManager();
	Shader &get_shader(const std::string &name);
};