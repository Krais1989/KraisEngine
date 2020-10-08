
#include "pch.h"
#include "CppUnitTest.h"

#include <KraisEngine/Core/Log.h>
#include <KraisEngine/Structs/DynArray.h>
#include <KraisEngine/Structs/LinkedList.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//#define KE_CORE_INFO(...)

#define STRCAT(msg1, msg2) return msg1##msg2

#define USECOUNT_STR(SP) (#SP" use count: " + std::to_string(SP.use_count()) + "\n").c_str()
#define PRINT_USECOUNT(SP) Logger::WriteMessage(USECOUNT_STR(SP))
#define LOG(msg) Logger::WriteMessage((msg+"\n").c_str())

namespace Tests
{
	class V1 {
	public:
		int m_a;
		V1(int a) : m_a(a) { }
		virtual void Print() {
			std::cout << "V1" << std::endl;
		}

	};

	class V2 : public V1 {
	public:
		int m_b;
		V2(int a, int b) : V1(a), m_b(b) { }

		void Print() override {
			std::cout << "V2" << std::endl;
		}
	};

	class V3 : public V2 {
	public:
		long long m_c;
		V3(int a, int b, long long c) : V2(a, b), m_c(c) { }
	};

	class V4 {
	public:
		int m_c;
		long long m_d;
		V4(int c, long long d) : m_c(c), m_d(d) { }
	};

	class V5 {
	public:
		int m_e;
		V5(int e) : m_e(e) { }
	};

	class V6 : public V4, public V5 {
	public:
		int m_f;
		int m_g;
		char m_str1;
		char m_str2;
		int m_h;
		V6(int c, int d, int e, int f, int g, int h) 
			: V4(c,d), V5(e), m_f(f), m_g(g), m_h(h), m_str1('s'), m_str2('t')
		{ 
		}
	};

	struct A {
		int a;
		int b;

		friend std::ostream& operator<< (std::ostream& os, const A& a) {
			os << "{" << std::to_string(a.a).c_str() << ":" << std::to_string(a.b) << "}";
			return os;
		}

		bool operator== (const A& other) const { return a == other.a && b == other.b; }
		bool operator!= (const A& other) const { !(*this == other); }

		virtual std::string toString() {
			std::string result = "{" + std::to_string(a) + ":" + std::to_string(b) + "}";
			return result;
		}

		A() : a(0), b(0) {
			std::string info(toString() + " Data construction default");
			LOG(info);
		}
		A(int ia, int ib) : a(ia), b(ib) {
			std::string info(toString() + " Data construction");
			LOG(info);
		}

		A(A&&) = default;

		~A() {
			std::string info(toString() + " Data destruction");
			LOG(info);
		}
	};

	template<typename T>
	void print_usecount(std::shared_ptr<T>& sp) {
		Logger::WriteMessage(("use count: " + std::to_string(sp.use_count()) + "\n").c_str());
	}

	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(TestVirtual) {

			V1 v1(1);
			V2 v2(1, 2);
			V3 v3(1, 2, 3);

			V4 v4(4, 5);
			V5 v5(4);
			V6 v6(4, 5, 6, 7, 8,9);


			/*std::string info1("v1: " + std::to_string(sizeof(v1)) + "\n");
			std::string info2("v2: " + std::to_string(sizeof(v2)) + "\n");
			std::string info3("v3: " + std::to_string(sizeof(v3)) + "\n");

			Logger::WriteMessage(info1.c_str());
			Logger::WriteMessage(info2.c_str());
			Logger::WriteMessage(info3.c_str());*/

		}

		TEST_METHOD(TestSmartPointers) {
			Assert::IsTrue(true);
			std::shared_ptr<A> a;
			//print_usecount(a);
			PRINT_USECOUNT(a);
			{
				std::shared_ptr<A> b = std::shared_ptr<A>(new A(1, 2));
				a = b;
				PRINT_USECOUNT(a);
				PRINT_USECOUNT(b);
			}
			PRINT_USECOUNT(a);
			LOG(a->toString());
		}

		TEST_METHOD(LinkedListTest) {

			LinkedList<A> list;

			auto a = list.Push({ 1,1 });
			auto b = list.Push({ 2,2 });
			auto d = list.Push({ 4,4 });
			auto e = list.Push({ 5,5 });

			auto c = list.Insert({ 3,3 }, 2);

			auto g = list.FindDataByElemFunc([](const LinkedList<A>::Elem& elem, int ind) { return elem.GetDataPtr()->a == 3; });
			auto g2 = list.FindDataByFunc([](const LinkedList<A>::Data& data, int ind) { return data.a == 3; });
			Assert::IsTrue(g == g2);

			Assert::IsTrue(*c == *list[2]);

			Assert::IsTrue(list.Exists(*a));
			Assert::IsTrue(list.Exists(*b));
			Assert::IsTrue(list.Exists(*c));
			Assert::IsTrue(list.Exists(*d));
			Assert::IsTrue(list.Exists(*e));

			PRINT_USECOUNT(a);
			PRINT_USECOUNT(b);
			PRINT_USECOUNT(c);
			PRINT_USECOUNT(d);
			PRINT_USECOUNT(e);

			list.GetSize() == 5;
			Assert::IsTrue(list.GetSize() == 5);
			Assert::IsTrue(&list.GetFirst() == &*a);
			Assert::IsTrue(&list.GetLast() == &*e);

			Assert::IsTrue(list.Remove(*a));
			Assert::IsFalse(list.Exists(*a));
			Assert::IsTrue(list.GetSize() == 4);
			Assert::IsTrue(&list.GetFirst() == &*b);
			Assert::IsTrue(&list.GetLast() == &*e);

			Assert::IsTrue(list.Remove(*e));
			Assert::IsFalse(list.Exists(*e));
			Assert::IsTrue(list.GetSize() == 3);
			Assert::IsTrue(&list.GetFirst() == &*b);
			Assert::IsTrue(&list.GetLast() == &*d);

			Assert::IsTrue(list.Remove(*c));
			Assert::IsFalse(list.Exists(*c));
			Assert::IsTrue(list.GetSize() == 2);
			Assert::IsTrue(&list.GetFirst() == &*b);
			Assert::IsTrue(&list.GetLast() == &*d);

			Assert::IsTrue(list.Remove(*b));
			Assert::IsTrue(list.Remove(*d));
			Assert::IsFalse(list.Exists(*b));
			Assert::IsFalse(list.Exists(*d));

			list.Clear();

			Assert::IsTrue(list.GetSize() == 0);
		}
		TEST_METHOD(DynArrayTest)
		{
			KE::Log::Init();

			DynArray<int> a(5);
			DynArray<int> b(a);
			DynArray<int> c(DynArray<int>(10));
			DynArray<int> d(std::move(DynArray<int>(10)));
			
			for (size_t i = 0; i < a.GetLength(); i++)
			{
				a[i] = i + 1;
				auto s = std::to_string(a[i]) + "\n";
				Logger::WriteMessage(s.c_str());
			}

			Logger::WriteMessage("\n");

			a.Resize(a.GetLength() * 2);
			for (size_t i = 0; i < a.GetLength(); i++)
			{
				a[i] = i + a.GetLength() + 1;

				auto s = std::to_string(a[i]) + "\n";
				Logger::WriteMessage(s.c_str());
			}

			KE_INFO("test");
			Assert::IsTrue(true);
		}
	};
}
