#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

namespace rendering {

class Shader
{
private:
	unsigned int m_id;
	std::unordered_map<std::string, int> m_uniforms;

	int get_location(const std::string &name);

public:
	Shader(std::ifstream &file);
	~Shader();

	unsigned int id() const;
	void use() const;

	void set_uniform(const std::string &name, int value);
	void set_uniform(const std::string &name, float value);
	void set_uniform(const std::string &name, glm::mat4 &value);
	void set_uniform(const std::string &name, glm::vec3 &value);
};

}