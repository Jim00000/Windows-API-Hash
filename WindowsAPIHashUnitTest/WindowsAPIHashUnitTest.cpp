#include "pch.h"
#include "CppUnitTest.h"
#include <WindowsAPIHash.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace WindowsAPIHashUnitTest
{
	TEST_CLASS(WindowsAPIHashUnitTest)
	{
	public:
		
		TEST_METHOD(TestDifferentInputType1)
		{
			const auto hash = WINAPIHash::GetAPIHash(L"user32.dll"s, "MessageBoxA");
			Assert::AreEqual(hash, 0x7568345ULL);
		}

		TEST_METHOD(TestDifferentInputType2)
		{
			const auto hash = WINAPIHash::GetAPIHash(L"user32.dll"s, "MessageBoxA"s);
			Assert::AreEqual(hash, 0x7568345ULL);
		}

		TEST_METHOD(TestDifferentInputType3)
		{
			const auto hash = WINAPIHash::GetAPIHash(L"user32.dll", "MessageBoxA");
			Assert::AreEqual(hash, 0x7568345ULL);
		}

		TEST_METHOD(TestDifferentInputType4)
		{
			const auto hash = WINAPIHash::GetAPIHash(L"user32.dll", "MessageBoxA"s);
			Assert::AreEqual(hash, 0x7568345ULL);
		}

		TEST_METHOD(TestDifferentInputType5)
		{
			const auto hash = WINAPIHash::GetAPIHash("user32.dll", "MessageBoxA");
			Assert::AreEqual(hash, 0x7568345ULL);
		}

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

		TEST_METHOD(TestMethod3)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "FindNextFileA");
			Assert::AreEqual(hash, 0xF76C45E7ULL);
		}

		TEST_METHOD(TestMethod4)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "FindFirstFileA");
			Assert::AreEqual(hash, 0x95DA3590ULL);
		}

		TEST_METHOD(TestMethod5)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "CreateFileA");
			Assert::AreEqual(hash, 0x4FDAF6DAULL);
		}

		TEST_METHOD(TestMethod6)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "CreateFileMappingA");
			Assert::AreEqual(hash, 0x23F9CD0AULL);
		}

		TEST_METHOD(TestMethod7)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "MapViewOfFile");
			Assert::AreEqual(hash, 0x757AEF13ULL);
		}

		TEST_METHOD(TestMethod8)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "UnmapViewOfFile");
			Assert::AreEqual(hash, 0x257CA71EULL);
		}

		TEST_METHOD(TestMethod9)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "WriteFile");
			Assert::AreEqual(hash, 0x5BAE572DULL);
		}

		TEST_METHOD(TestMethod10)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "MoveFile");
			Assert::AreEqual(hash, 0x36B39FEDULL);
		}

		TEST_METHOD(TestMethod11)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "DeleteFileA");
			Assert::AreEqual(hash, 0x13DD2ED7ULL);
		}

		TEST_METHOD(TestMethod12)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "CloseHandle");
			Assert::AreEqual(hash, 0x528796C6ULL);
		}

		TEST_METHOD(TestMethod13)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "RtlCopyMemory");
			Assert::AreEqual(hash, 0x4F8D91FEULL);
		}

		TEST_METHOD(TestMethod14)
		{
			const auto hash = WINAPIHash::GetAPIHash("kernel32.dll", "MoveFileExA");
			Assert::AreEqual(hash, 0x45FF3DECULL);
		}
	};
}
