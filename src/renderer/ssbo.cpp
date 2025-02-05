#include <renderer/ssbo.h>
#include <iostream>

ssbo::ssbo(const auto* data, unsigned int binding) : m_Binding(binding)  {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(PointLight), nullptr, GL_DYNAMIC_DRAW);
}

ssbo::~ssbo() { glDeleteBuffers(1, &ID); }

void ssbo::setBinding() const { glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_Binding, ID); }

void ssbo::Bind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID); }

void ssbo::Unbind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }