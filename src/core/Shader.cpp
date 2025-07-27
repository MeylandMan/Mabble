#include "../../include/mabble/mabble.h"

namespace Mabble
{
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		MABBLE_ASSERT(!Exists(name) && "This shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::LoadFile(const std::string& filepath)
	{
		auto shader = CreateShaderFromFile(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadFile(const std::string& name, const std::string& filepath)
	{
		auto shader = CreateShaderFromFile(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadSource(const std::string& shaderSrc)
	{
		auto shader = CreateShaderFromSource(shaderSrc);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadSource(const std::string& name, const std::string& shaderSrc)
	{
		auto shader = CreateShaderFromSource(shaderSrc);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadSources(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		auto shader = CreateShaderFromSources(vertexSrc, fragmentSrc);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadSources(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		auto shader = CreateShaderFromSources(vertexSrc, fragmentSrc);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		MABBLE_ASSERT(Exists(name) && "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}