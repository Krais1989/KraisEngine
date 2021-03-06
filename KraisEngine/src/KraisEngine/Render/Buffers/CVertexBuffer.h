#pragma once

#include "ke_pch.h"
#include "IBindableBuffer.h"
#include "CBufferLayout.h"

namespace KE
{
	class CVertexBuffer : public IBindableBuffer {
	protected:
		using data_t = unsigned char;

		std::vector<data_t> m_Data;
		//std::unique_ptr<data_t[]> m_Data;
		//size_t m_DataSize;
		CBufferLayout m_Layout;

	public:
		CVertexBuffer(CBufferLayout layout, std::initializer_list<data_t> data)
			: m_Layout(layout), m_Data(data)
		{
		}

		size_t GetSizeInBytes() const { return m_Data.size(); }
		const std::vector<data_t>& GetData() const { return m_Data; }
		const void* GetRawPointer() { return (const void*)m_Data.front(); }
	};


}