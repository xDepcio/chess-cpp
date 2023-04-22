#include "pch.h"
#include "CppUnitTest.h"
#include "../ChessLib/Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessUnitTests
{
	TEST_CLASS(ChessUnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Board<int> b;
			b.setvalue(2);
			Assert::AreEqual(2, b.getValue());
		}
	};
}
