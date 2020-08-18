#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/Log.h>

#define KE_DYNARRAY_DEFAULT_SIZE 100

template<typename T>
class DynArray
{

private:
	T* m_data;
	int m_length;
	bool m_isMoveSemantic;

public:

	int GetLength() const { return m_length; }
	const T* const GetRawData() const { return m_data; }

	T& operator[] (int index) const {
		//if (index > m_length - 1)
		//	throw std::exception("Index out of bound!");
		return m_data[index];
	}

	/*void operator[] (int index, const T& value) {
		m_data[index] = value;
	}*/

	void Resize(int newSize) {
		if (newSize == m_length) return;
		if (newSize < m_length) {
			//KE_CORE_WARN("DynArray: new size ({}) is smaller than old one ({}). Some data will be lost.", newSize, m_length);
		}
		T* newData = new T[newSize];
		memcpy(newData, m_data, m_length * sizeof(T));
		delete[] m_data;
		m_data = newData;

		m_length = newSize;
	}

	DynArray(int length = KE_DYNARRAY_DEFAULT_SIZE)
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
		int bsize = other.GetLength() * sizeof(T);
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