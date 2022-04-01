#include "pch.h"
#include <list>
#include "CppUnitTest.h"
#include "../RBTree/RBT.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{

	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(find)
		{
			RBTree<int> tree;
			tree.insert(1, 1);
			tree.insert(2, 2);
			tree.insert(3, 3);
			tree.insert(4, 4);
			tree.insert(5, 5);
			Assert::IsTrue(tree.find(1) != nullptr);

		}

		TEST_METHOD(remove)
		{
			RBTree<int> tree;
			tree.insert(1, 1);
			tree.insert(2, 2);
			tree.insert(3, 3);
			tree.insert(4, 4);
			tree.insert(5, 5);
			tree.remove(1);
			Assert::IsTrue(tree.find(1) == nullptr);
		}

		TEST_METHOD(insert)
		{
			RBTree<int> tree;
			tree.insert(1, 1);
			tree.insert(2, 2);
			tree.insert(3, 3);
			tree.insert(4, 4);
			tree.insert(5, 5);
			Assert::IsTrue(tree.find(1) != nullptr);
		}

		TEST_METHOD(values)
		{
			RBTree<int> tree;
			tree.insert(1, 1);
			tree.insert(2, 2);
			tree.insert(3, 3);
			tree.insert(4, 4);
			tree.insert(5, 5);

			list<int> list, list_t;
			tree.get_values(list);
			list_t = {2,1,4,3,5};

			Assert::IsTrue(list == list_t);
		}

		TEST_METHOD(keys)
		{
			RBTree<int> tree;
			tree.insert(1, 1);
			tree.insert(2, 2);
			tree.insert(3, 3);
			tree.insert(4, 4);
			tree.insert(5, 5);

			list<int> list, list_t;
			tree.get_keys(list);
			list_t = { 2,1,4,3,5 };

			Assert::IsTrue(list == list_t);
		}

		TEST_METHOD(clear)
		{

			RBTree<int> tree;
			tree.insert(1, 1);
			tree.insert(2, 2);
			tree.insert(3, 3);
			tree.insert(4, 4);
			tree.insert(5, 5);
			tree.clear();
			Assert::IsTrue(tree.is_empty());
		}
	};
}
