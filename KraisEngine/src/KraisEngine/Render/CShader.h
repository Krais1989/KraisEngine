#pragma once

#include <KraisEngine/Core/Core.h>

#include <glm/glm.hpp>

namespace KE {

	class CShader
	{
	public:
		virtual ~CShader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetInt(const char* name, int i) = 0;
		virtual void SetFloat(const char* name, float f) = 0;
		virtual void SetMatrix4f(const char* name, glm::mat4& mat) = 0;

		static std::shared_ptr<CShader> CreateFromData(const std::string name, const char* vertexSrc, const char* fragSrc);
		static std::shared_ptr<CShader> CreateFromFile(const std::string name, const std::filesystem::path& vertexPath, const std::filesystem::path& fragPath);

		virtual unsigned int GetID() const = 0;

	protected:
	};

}

