#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// Функція для створення вхідного файлу з числами
void createInputFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Помилка відкриття файлу для запису\n");
        return;
    }

    int num;
    printf("Введіть цілі числа (введіть 0 для завершення):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0) break;
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);
}

// Функція для розділення чисел на парні та непарні файли
void splitNumbers(const char* sourceFile, const char* evenFile, const char* oddFile) {
    FILE* source = fopen(sourceFile, "rb");
    FILE* even = fopen(evenFile, "wb");
    FILE* odd = fopen(oddFile, "wb");

    if (source == NULL || even == NULL || odd == NULL) {
        printf("Помилка відкриття файлів\n");
        return;
    }

    int num;
    while (fread(&num, sizeof(int), 1, source) == 1) {
        if (num % 2 == 0) {
            fwrite(&num, sizeof(int), 1, even);
        }
        else {
            fwrite(&num, sizeof(int), 1, odd);
        }
    }

    fclose(source);
    fclose(even);
    fclose(odd);
}

// Функція для виведення вмісту файлу
void displayFileContents(const char* filename, const char* description) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Помилка відкриття файлу для читання\n");
        return;
    }

    printf("\n%s:\n", description);
    int num;
    while (fread(&num, sizeof(int), 1, file) == 1) {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char inputFilename[100];
    const char* evenFilename = "even.bin";
    const char* oddFilename = "odd.bin";

    printf("Введіть ім'я вхідного файлу: ");
    scanf("%s", inputFilename);

    // Створення вхідного файлу
    createInputFile(inputFilename);

    // Розділення чисел на парні та непарні файли
    splitNumbers(inputFilename, evenFilename, oddFilename);

    // Виведення вмісту всіх файлів
    displayFileContents(inputFilename, "Початкові числа");
    displayFileContents(evenFilename, "Парні числа");
    displayFileContents(oddFilename, "Непарні числа");

    return 0;
}
