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
		ELayoutElementType m_ElementType;
		size_t m_ElementsCount;
	public:
		const size_t& GetElementsCount() const { return m_ElementsCount; }
		size_t GetElementSize() const { return GetSizeOfElementType(m_ElementType); }
		size_t GetAttributeSize() const { return GetSizeOfElementType(m_ElementType) * m_ElementsCount; }
		const ELayoutElementType& GetType() const { return m_ElementType; }
	};

	class CBufferLayout {
	protected:
		std::vector<CBufferLayoutAttribute> m_Attributes;
	public:
		CBufferLayout(std::initializer_list<CBufferLayoutAttribute> attributes)
			:m_Attributes(attributes)
		{
		}

		size_t GetAttributesCount() const { return m_Attributes.size(); }
		const CBufferLayoutAttribute& GetAttribute(size_t i) { CheckAttributeIndex(i); return m_Attributes[i]; }
		bool CheckAttributeIndex(size_t i) const {
			//KE_ASSERT(, "Attribute Index invalid range: {0}", i);
			return i >= 0 && i < m_Attributes.size();
		}

		const CBufferLayoutAttribute& operator[](size_t i) { return GetAttribute(i); }
	};

}


