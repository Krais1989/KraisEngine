#pragma once

#include <glad/glad.h>
#include "KraisEngine/Render/Buffers/CBufferLayout.h"

namespace KE
{
	static unsigned int GetElementOpenGLType(ELayoutElementType type) {
		switch (type)
		{
		case KE::ELayoutElementType::Float:
			return GL_FLOAT;
		case KE::ELayoutElementType::Integer:
			return GL_INT;
		case KE::ELayoutElementType::UnsignedInteger:
			return GL_UNSIGNED_INT;
		default:
			KE_CORE_ERROR("OpenGL type not mapped to Element type: {0}", type);
			throw std::invalid_argument("OpenGL type not mapped to Element type {0}");
			break;
		}
	}
}