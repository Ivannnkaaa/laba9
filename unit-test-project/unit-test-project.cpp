#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/book_subscription.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
	TEST_CLASS(unittestproject)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Assert::Fail();
		}

        TEST_METHOD(TestDurationSeconds)
        {
            CallRecord record = { "1234567890", "26.05.25", "14:22:30", "01:30:00", "�����", 0.50 };
            Assert::AreEqual(5400, record.duration_seconds(), L"�������� �������� ����������������� ������ � �������.");
        }

        TEST_METHOD(TestIsMobile)
        {
            CallRecord record1 = { "1234567890", "26.05.25", "14:22:30", "00:10:00", "���������", 0.50 };
            CallRecord record2 = { "9876543210", "25.05.25", "09:15:45", "00:07:30", "�����", 1.20 };

            Assert::IsTrue(record1.is_mobile(), L"���������, ��� ������ �������� ���������.");
            Assert::IsFalse(record2.is_mobile(), L"���������, ��� ������ �� �������� ���������.");
        }

        TEST_METHOD(TestIsNovember2021)
        {
            CallRecord record1 = { "5678901234", "15.11.2021", "10:15:30", "00:05:00", "��������", 1.20 };
            CallRecord record2 = { "3456789012", "23.05.25", "11:40:50", "00:20:30", "�������������", 2.50 };

            Assert::IsTrue(record1.is_november_2021(), L"���������, ��� ���� ��������� � ������ 2021 ����.");
            Assert::IsFalse(record2.is_november_2021(), L"���������, ��� ���� �� ��������� � ������ 2021 ����.");
        }

        TEST_METHOD(TestOperatorGreater)
        {
            CallRecord record1 = { "1234567890", "26.05.25", "14:22:30", "02:00:00", "�����", 0.50 };
            CallRecord record2 = { "9876543210", "25.05.25", "09:15:45", "01:30:00", "��������", 1.20 };

            Assert::IsTrue(record1 > record2, L"���������, ��� ������ ������ ������ �������.");
            Assert::IsFalse(record2 > record1, L"���������, ��� ������ ������ ������ �������.");
        }
	};
}
