#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../LR_12.1 C/LR_12.1 C.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		// ������� ��� ������� ����� �� ����� � ������
		std::vector<int> readNumbersFromFile(const char* filename) {
			FILE* file = fopen(filename, "rb");
			std::vector<int> numbers;
			if (file != nullptr) {
				int num;
				while (fread(&num, sizeof(int), 1, file) == 1) {
					numbers.push_back(num);
				}
				fclose(file);
			}
			return numbers;
		}

		TEST_METHOD(TestSplitNumbers)
		{
			// ��������� �������� �����
			const char* sourceFile = "test_input.bin";
			const char* evenFile = "test_even.bin";
			const char* oddFile = "test_odd.bin";

			// ����� �������� ����� � ������� ����
			FILE* file = fopen(sourceFile, "wb");
			int testData[] = { 1, 2, 3, 4, 5, 6 };
			fwrite(testData, sizeof(int), 6, file);
			fclose(file);

			// ������ ������� ��������� �����
			splitNumbers(sourceFile, evenFile, oddFile);

			// �������� ������ �����
			std::vector<int> evenNumbers = readNumbersFromFile(evenFile);
			std::vector<int> expectedEven = { 2, 4, 6 };
			Assert::IsTrue(evenNumbers == expectedEven, L"���� ����� �� ���������� ����������");

			// �������� �������� �����
			std::vector<int> oddNumbers = readNumbersFromFile(oddFile);
			std::vector<int> expectedOdd = { 1, 3, 5 };
			Assert::IsTrue(oddNumbers == expectedOdd, L"������ ����� �� ���������� ����������");
		}
	};
}
