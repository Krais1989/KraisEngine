#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/Log.h>

#define KE_DYNARRAY_DEFAULT_SIZE 100

template<typename T>
class DynArray
{

private:
	T* m_data;
	size_t m_length;
	bool m_isMoveSemantic;

public:

	size_t GetLength() const { return m_length; }
	const T* const GetRawData() const { return m_data; }
	bool CheckIndex(size_t ind) const {
		return ind >= 0 && ind < m_length;
	}
	void CheckIndexWithThrow(size_t ind) {
		if (!CheckIndex(ind)) {
			#if KE_CONTAINER_DEBUG == 1
			__debugbreak();
			#endif
			throw std::out_of_range("wrong index");
		}
	}

	T& operator[] (size_t index) {
		CheckIndexWithThrow(index);
		return m_data[index];
	}
	const T& operator[] (size_t index) const {
		CheckIndexWithThrow(index);
		return m_data[index];
	}

	void Resize(size_t newSize) {
		if (newSize == m_length) return;
		if (newSize < m_length) {
			//KE_CORE_WARN("DynArray: new size ({}) is smaller than old one ({}). Some data will be lost.", newSize, m_length);
		}
		T* newData = new T[newSize];
		memcpy(newData, m_data, m_length * sizeof(T));
		memset(newData, 0, m_length * sizeof(T));
		delete[] m_data;
		m_data = newData;

		m_length = newSize;
	}

	DynArray(size_t length = KE_DYNARRAY_DEFAULT_SIZE)
		: m_length(length)
		, m_data(new T[length])
		, m_isMoveSemantic(false)
	{
		KE_CORE_INFO("DynArray construction by length");
		//m_data = new T[length];
		//m_data = new T[length];
	}

	DynArray(const DynArray& other) {
		KE_CORE_INFO("DynArray construction by copy");

		Resize(other.GetLength());
		size_t bsize = other.GetLength() * sizeof(T);
		memcpy(m_data, other.GetRawData(), bsize);
	}

	DynArray(DynArray&& other) {
		KE_CORE_INFO("DynArray construction by move semantics");

		m_data = (T*)other.GetRawData();
		m_length = other.GetLength();
		other.m_isMoveSemantic = true;
	}

	virtual ~DynArray() {
		KE_CORE_INFO("DynArray destruction");

		if (!m_isMoveSemantic)
		{
			KE_CORE_INFO("delete[] m_data");
			delete[] m_data;
		}

	}
};