
#include "pch.h"
#include "CppUnitTest.h"

#include <KraisEngine/Core/Log.h>
#include <KraisEngine/Structs/GridChunk2D.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#define LOG(msg) Logger::WriteMessage((msg+"\n").c_str())
#define LOGN(msg) Logger::WriteMessage((msg+"\n").c_str())

void* operator new(size_t size) {
	//LOG(std::string("Alloc ") + std::to_string(size) + std::string(" bytes"));
	return malloc(size);
}

void operator delete(void* p) {
	//LOG(std::string("Free memory: "));
	free(p);
}

namespace TestGrid {

	class Tile
	{
	public:
		using tile_type = int;
	private:
		tile_type m_type;
	public:
		~Tile() { LOG(std::string("Tile Destruct: ") + std::to_string(m_type)); }

		Tile() : m_type(0) {
			LOG(std::string("Tile Construct default: ") + std::to_string(m_type));
		}
		Tile(tile_type ttype) :m_type(ttype) {
			LOG(std::string("Tile Construct: ") + std::to_string(m_type));
		}
		Tile(const Tile& other) : m_type(other.m_type) {
			LOG(std::string("Tile Copy Construct: ") + std::to_string(other.m_type));
		}
		Tile(Tile&& other) : m_type{ std::exchange(other.m_type,0) } {
			LOG(std::string("Tile Move Construct: ") + std::to_string(other.m_type));
		}

		Tile& operator= (const Tile& other) {
			if (&other != this) {
				m_type = other.m_type;
			}
			return *this;
		}

		Tile& operator= (Tile&& other) noexcept {
			if (this != &other)
				m_type = std::exchange(other.m_type, 0);
			return *this;
		}

		tile_type& GetType() { return m_type; }
		void SetType(tile_type ttype) { m_type = ttype; }
	};

	TEST_CLASS(TestGrid) {
	public:
		TEST_METHOD(Test1) {

			auto i = new int(5);
			Logger::WriteMessage(typeid(i).name());

			//const int w = 2;
			//const int h = 3;

			//GridChunk2D<Tile, w, h> grid_chunk;
			//Assert::IsTrue(w == grid_chunk.GetWidth() && h == grid_chunk.GetHeight());

			//{
			//	// TODO: повторное копирование T в сетку. (первое было при инициализации сетки)
			//	for (int y = 0; y < h; y++)
			//	{
			//		for (int x = 0; x < w; x++) {
			//			// TODO: вместо создания и отправки T в grid_chunk, нужно создавать сразу в grid_chunk, передавая аргументы
			//			grid_chunk.SetField(x, y, 1 + x + y * w); // copy rvalue of Tile
			//		}
			//	}
			//}

			//int newval = 5;
			//Tile& i1 = grid_chunk.GetField(0, 0);
			//i1.SetType(newval);
			//Tile& i1t = grid_chunk.GetField(0, 0);
			//Assert::IsTrue(newval == i1t.GetType());
		}
	};
}