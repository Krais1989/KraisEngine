#pragma once

namespace KE
{
	class CGraphicsContext {
	public:
		virtual ~CGraphicsContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;

		static std::unique_ptr<CGraphicsContext> Create(void* window);
	};
}