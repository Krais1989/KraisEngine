#pragma once

#include "ke_pch.h"

namespace KE {

	struct SVertexAttributes_Pos
	{
		float POS_X = 0;
		float POS_Y = 0;
		float POS_Z = 0;
	};

	struct SVertexAttributes_PosTex
	{
		float POS_X = 0;
		float POS_Y = 0;
		float POS_Z = 0;
		float TEX_U = 0;
		float TEX_V = 0;
	};

	struct SVertexAttributes_PosTexColor {
		float POS_X = 0;
		float POS_Y = 0;
		float POS_Z = 0;
		float TEX_U = 0;
		float TEX_V = 0;
		float COL_R = 0;
		float COL_G = 0;
		float COL_B = 0;
		float COL_A = 1.0f;
	};

	class IBindableBuffer {
	public:
		virtual void Bind() = 0;
	};

	template<typename TA>
	class CBuffer : public IBindableBuffer {
	public:

		CBuffer() = default;
		CBuffer(std::vector<TA>&& data) : m_ID(0) { Init(std::move(data)); }
		virtual ~CBuffer() { Dispose(); }

		virtual void Init(std::vector<TA> data) = 0;
		virtual void Dispose() = 0;
		virtual void Bind() = 0;
		virtual int GetID() { return m_ID; }
	protected:
		unsigned int m_ID;
	};

	class CArrayBuffer
	{
	public:
		CArrayBuffer() = default;
		virtual ~CArrayBuffer()
		{
			Dispose();
		}
		virtual void Init(std::vector<IBindableBuffer>& buffers) = 0;
		virtual void Bind() = 0;
		virtual void Dispose() = 0;
	protected:
		unsigned int m_ID = 0;
	};
}


