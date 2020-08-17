#include "pch.h"

#include "CppUnitTest.h"

#include <KraisEngine/Core/Log.h>
#include <KraisEngine/Structs/DynArray.h>
#include <KraisEngine/Structs/LinkedList.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//#define KE_CORE_INFO(...)

namespace Tests
{
	struct A {
		int a;
		int b;
	};

	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(LinkedListTest) {

			LinkedList<A> list;
			auto& a = list.Push({ 1,1 });
			auto& b = list.Push({ 2,2 });
			auto& c = list.Push({ 3,3 });
			auto& d = list.Push({ 4,4 });
			auto& e = list.Push({ 5,5 });

			Assert::IsTrue(list.Find(a));
			Assert::IsTrue(list.Find(b));
			Assert::IsTrue(list.Find(c));
			Assert::IsTrue(list.Find(d));
			Assert::IsTrue(list.Find(e));

			Assert::AreEqual(list.GetSize(), 5);
			Assert::IsTrue(&list.GetFirst() == &a);
			Assert::IsTrue(&list.GetLast() == &e);

			list.Remove(a);
			Assert::IsFalse(list.Find(a));
			Assert::AreEqual(list.GetSize(), 4);
			Assert::IsTrue(&list.GetFirst() == &b);
			Assert::IsTrue(&list.GetLast() == &e);

			list.Remove(e);
			Assert::IsFalse(list.Find(e));
			Assert::AreEqual(list.GetSize(), 3);
			Assert::IsTrue(&list.GetFirst() == &b);
			Assert::IsTrue(&list.GetLast() == &d);

			list.Remove(c);
			Assert::IsFalse(list.Find(c));
			Assert::AreEqual(list.GetSize(), 2);
			Assert::IsTrue(&list.GetFirst() == &b);
			Assert::IsTrue(&list.GetLast() == &d);

			list.Clear();
			Assert::IsFalse(list.Find(b));
			Assert::IsFalse(list.Find(d));
			Assert::AreEqual(list.GetSize(), 0);
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
