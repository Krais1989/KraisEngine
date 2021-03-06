#pragma once

#include "KraisEngine/Render/Buffers/CVertexBuffer.h"
#include "KraisEngine/Render/Buffers/CIndexBuffer.h"
#include "KraisEngine/Render/Buffers/CArrayBuffer.h"


#include "Platform/OpenGL/CVertexBuffer_OpenGL.h"
#include "Platform/OpenGL/CIndexBuffer_OpenGL.h"
#include "Platform/OpenGL/CArrayBuffer_OpenGL.h"

namespace KE {

	template<typename T>
	class CPlatformFactory {
	public:
		template<typename ... Args>
		std::unique_ptr<T> Create(Args... args) = 0;
	};

	template<>
	class CPlatformFactory<CVertexBuffer> {
	public:
		template<typename ... Args>
		std::unique_ptr<CVertexBuffer> Create(Args&&... args) {
			return std::make_unique<CVertexBuffer_OpenGL>(std::forward<Args>(args)...);
		}
	};

	template<>
	class CPlatformFactory<CIndexBuffer> {
	public:
		template<typename ... Args>
		std::unique_ptr<CIndexBuffer> Create(Args&&... args) {
			return std::make_unique<CIndexBuffer_OpenGL>(std::forward<Args>(args)...);
		}
	};

	template<>
	class CPlatformFactory<CArrayBuffer> {
	public:
		template<typename ... Args>
		std::unique_ptr<CArrayBuffer> Create(Args&&... args) {
			return std::make_unique<CArrayBuffer_OpenGL>(std::forward<Args>(args)...);
		}
	};
}