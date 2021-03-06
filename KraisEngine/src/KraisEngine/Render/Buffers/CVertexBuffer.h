#pragma once

#include "ke_pch.h"
#include "IBindableBuffer.h"
#include "CBufferLayout.h"

namespace KE
{
	class CVertexBuffer : public IBindableBuffer {

	public:
		using data_t = unsigned char;
		using storage_t = std::vector<data_t>;

	protected:

		storage_t m_Data;
		CBufferLayout m_Layout;

	public:

		CVertexBuffer(CBufferLayout layout, const data_t* raw, size_t raw_size)
			: m_Layout(layout), m_Data(raw, raw + raw_size)
		{
		}

		CVertexBuffer(CBufferLayout layout, std::initializer_list<data_t> data)
			: m_Layout(layout), m_Data(data)
		{
		}

		CVertexBuffer(CBufferLayout layout, const storage_t& data)
			: m_Layout(layout), m_Data(data)
		{
		}

		CVertexBuffer(CBufferLayout layout, storage_t&& data)
			: m_Layout(layout), m_Data(std::move(data))
		{
		}

		size_t GetSizeInBytes() const { return m_Data.size(); }
		const storage_t& GetData() const { return m_Data; }
		const void* GetRawPointer() { return (const void*)m_Data.front(); }
	};


}