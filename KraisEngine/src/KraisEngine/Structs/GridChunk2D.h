#pragma once

#include <ke_pch.h>
#include <KraisEngine/Core/Log.h>

template<typename T, size_t W, size_t H>
class GridChunk2D
{
private:
	size_t m_width = W;
	size_t m_height = H;
	T m_data[H][W];
public:

	constexpr size_t GetWidth() { return m_width; }
	constexpr size_t GetHeight() { return m_height; }

	GridChunk2D() {};
	~GridChunk2D() {}

	T& GetField(const size_t& x, const size_t& y) {
		if (x >= m_width || y >= m_height)
			__debugbreak();
		return *m_data[y, x];
	}

	void SetField(const size_t& x, const size_t& y, const T& field) {
		GetField(x, y) = field;
	}

private:

};