#pragma once

#include "IBindableBuffer.h"

namespace KE
{
	class CIndexBuffer : public IBindableBuffer {
	protected:
		using data_t = unsigned int;
		std::vector<data_t> m_Data;
	public:
		const size_t ElementSize = sizeof(data_t);

		CIndexBuffer(std::initializer_list<data_t> data)
			: m_Data(data)
		{
		}

		const std::vector<data_t>& GetData() const { return m_Data; }
		size_t GetCount() const { return m_Data.size(); }
		size_t GetSizeInBytes() const { return CIndexBuffer::ElementSize * m_Data.size(); }
		const void* GetRawPointer() { return (const void*)m_Data.front(); }
	};


}