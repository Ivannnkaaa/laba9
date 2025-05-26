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
            CallRecord record = { "1234567890", "26.05.25", "14:22:30", "01:30:00", "город", 0.50 };
            Assert::AreEqual(5400, record.duration_seconds(), L"Проверка перевода продолжительности звонка в секунды.");
        }

        TEST_METHOD(TestIsMobile)
        {
            CallRecord record1 = { "1234567890", "26.05.25", "14:22:30", "00:10:00", "мобильный", 0.50 };
            CallRecord record2 = { "9876543210", "25.05.25", "09:15:45", "00:07:30", "город", 1.20 };

            Assert::IsTrue(record1.is_mobile(), L"Ожидалось, что звонок является мобильным.");
            Assert::IsFalse(record2.is_mobile(), L"Ожидалось, что звонок НЕ является мобильным.");
        }

        TEST_METHOD(TestIsNovember2021)
        {
            CallRecord record1 = { "5678901234", "15.11.2021", "10:15:30", "00:05:00", "межгород", 1.20 };
            CallRecord record2 = { "3456789012", "23.05.25", "11:40:50", "00:20:30", "международный", 2.50 };

            Assert::IsTrue(record1.is_november_2021(), L"Ожидалось, что дата находится в ноябре 2021 года.");
            Assert::IsFalse(record2.is_november_2021(), L"Ожидалось, что дата НЕ находится в ноябре 2021 года.");
        }

        TEST_METHOD(TestOperatorGreater)
        {
            CallRecord record1 = { "1234567890", "26.05.25", "14:22:30", "02:00:00", "город", 0.50 };
            CallRecord record2 = { "9876543210", "25.05.25", "09:15:45", "01:30:00", "межгород", 1.20 };

            Assert::IsTrue(record1 > record2, L"Ожидалось, что первый звонок дольше второго.");
            Assert::IsFalse(record2 > record1, L"Ожидалось, что второй звонок короче первого.");
        }
	};
}
