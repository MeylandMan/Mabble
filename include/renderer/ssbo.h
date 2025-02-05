#pragma once
#include <glad/glad.h>
#include <vector>
#include <renderer/lights.h>

class ssbo
{
public:
	ssbo(const auto* data, unsigned int count);
	~ssbo();

	void Bind() const;
	void setBinding() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int ID;
	unsigned int m_Binding;
};