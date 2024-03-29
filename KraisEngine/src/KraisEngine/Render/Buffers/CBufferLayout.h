#pragma once

#include "ke_pch.h"
#include "KraisEngine/Core/Core.h"

namespace KE {

	enum class ELayoutElementType {
		Float,
		Integer,
		UnsignedInteger
	};

	static size_t GetSizeOfElementType(const ELayoutElementType& type) {
		switch (type)
		{
		case ELayoutElementType::Float:
			return sizeof(float);
		case ELayoutElementType::Integer:
			return sizeof(int);
		case ELayoutElementType::UnsignedInteger:
			return sizeof(unsigned int);
		default:
			KE_CORE_ERROR("Undefined element type: {0}", type);
			break;
		}
	}

	class CBufferLayoutAttribute {
	protected:
		friend class CBufferLayout;

		ELayoutElementType m_ElementType;
		size_t m_ElementsCount;
		size_t m_Offset = 0;
	public:

		CBufferLayoutAttribute(ELayoutElementType type, size_t elems_count)
			:m_ElementType(type), m_ElementsCount(elems_count)
		{
		}

		const size_t& GetOffset() const { return m_Offset; }
		const size_t& GetElementsCount() const { return m_ElementsCount; }
		const ELayoutElementType& GetType() const { return m_ElementType; }
		size_t GetElementSize() const { return GetSizeOfElementType(m_ElementType); }
		size_t GetAttributeSize() const { return GetSizeOfElementType(m_ElementType) * m_ElementsCount; }
	};

	class CBufferLayout {
	protected:
		std::vector<CBufferLayoutAttribute> m_Attributes;
		size_t m_Stride;

		void CalculateElements() {
			size_t offset = 0;
			m_Stride = 0;
			for (auto& attr : m_Attributes) {
				attr.m_Offset = offset;
				offset += attr.GetAttributeSize();
				m_Stride += attr.GetAttributeSize();
			}
		}

	public:
		CBufferLayout(std::initializer_list<CBufferLayoutAttribute> attributes)
			:m_Attributes(attributes), m_Stride(0)
		{
			KE_CORE_INFO("CBufferLayout ctor initializer_list");
			CalculateElements();
		}

		CBufferLayout(CBufferLayout&& other) noexcept
			: m_Attributes(std::move(other.m_Attributes)), m_Stride(other.m_Stride)
		{
			KE_CORE_INFO("CBufferLayout ctor MOVE");
			CalculateElements();
		}

		CBufferLayout(const CBufferLayout& other) noexcept 
			: m_Attributes(other.m_Attributes), m_Stride(other.m_Stride)
		{
			KE_CORE_INFO("CBufferLayout ctor COPY");
			CalculateElements();
		}

		virtual ~CBufferLayout()
		{
			KE_CORE_INFO("CBufferLayout dtor ~");
		}

		const CBufferLayoutAttribute& operator[](size_t i) { return GetAttribute(i); }

		const size_t& GetStride() const { return m_Stride; }
		size_t GetAttributesCount() const { return m_Attributes.size(); }

		const CBufferLayoutAttribute& GetAttribute(size_t i) { CheckAttributeIndex(i); return m_Attributes[i]; }

		bool CheckAttributeIndex(size_t i) const {
			return i >= 0 && i < m_Attributes.size();
		}

	};

}


