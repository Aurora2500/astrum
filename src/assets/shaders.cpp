#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "shaders.hpp"

static unsigned int compile_shader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> message(length);
		glGetShaderInfoLog(id, length, &length, message.data());
		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cerr << length << message.data() << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int compile_program(const std::string &vertex_src, const std::string &fragment_src)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_src);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_src);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

Shader::Shader(std::ifstream &file)
{
	std::string line;
	std::string vertex_src;
	std::string fragment_src;
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	while (std::getline(file, line))
	{
		if (line.find("//shader ") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			switch (type)
			{
			case ShaderType::VERTEX:
				vertex_src += line + "\n";
				break;
			case ShaderType::FRAGMENT:
				fragment_src += line + "\n";
				break;
			default:
				break;
			}
		}
	}
	m_id = compile_program(vertex_src, fragment_src);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

unsigned int Shader::id() const
{
	return m_id;
}

void Shader::use() const
{
	glUseProgram(m_id);
}