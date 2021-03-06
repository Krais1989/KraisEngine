#pragma once

#include "IBindableBuffer.h"

namespace KE
{
	class CIndexBuffer : public IBindableBuffer {
	public:
		using data_t = unsigned int;
		using storage_t = std::vector<data_t>;

	protected:
		
		storage_t m_Data;
	public:
		const size_t ElementSize = sizeof(data_t);

		CIndexBuffer(std::initializer_list<data_t> data)
			: m_Data(data)
		{
		}

		CIndexBuffer(const storage_t& data)
			: m_Data(data)
		{
		}

		CIndexBuffer(storage_t&& data)
			: m_Data(std::move(data))
		{
		}

		const storage_t& GetData() const { return m_Data; }
		size_t GetCount() const { return m_Data.size(); }
		size_t GetSizeInBytes() const { return CIndexBuffer::ElementSize * m_Data.size(); }
		const void* GetRawPointer() { return (const void*)m_Data.data(); }
	};


}