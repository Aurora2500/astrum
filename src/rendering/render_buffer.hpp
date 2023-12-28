#pragma once

namespace rendering
{

class RenderBuffer
{
private:
	unsigned int m_id;

public:
	RenderBuffer();
	~RenderBuffer();

	void store(
			unsigned int width,
			unsigned int height);

	inline unsigned int id() const { return m_id; }
};

}