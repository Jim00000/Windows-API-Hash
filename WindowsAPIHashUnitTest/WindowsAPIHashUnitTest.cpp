#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsAPIHashUnitTest
{
	TEST_CLASS(WindowsAPIHashUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const auto hash = WINAPIHash::GetAPIHash("user32.dll", "MessageBoxA");
			Assert::AreEqual(hash, 0x7568345ULL);
		}

		TEST_METHOD(TestMethod2)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "ExitProcess");
			Assert::AreEqual(hash, 0x56A2B5F0ULL);
		}
	};
}
