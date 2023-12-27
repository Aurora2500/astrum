#pragma once
#include <string>
#include <fstream>

class Shader
{
private:
	unsigned int m_id;

public:
	Shader(std::ifstream &file);
	~Shader();

	unsigned int id() const;
	void use() const;
};