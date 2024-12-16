// 8archivan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath> 
#include <iomanip> 
#include <climits>

using namespace std;

int main() {
    const int rows = 3;        // Кількість рядків
    const int cols = 3;        // Кількість стовпців
    int array2D[rows][cols] = {  // Двовимірний масив
        {3, 5, 2},
        {1, 9, 8},
        {6, 4, 7}
    };
    int array1D[rows * cols];  // Одновимірний масив для результату
    const int totalElements = rows * cols;

    // Виведення початкового 2D масиву
    cout << "Initial 2D array:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << array2D[i][j] << " ";
        }
        cout << endl;
    }

    // Перетворення 2D масиву в 1D масив через асемблер
    __asm {
        lea esi, array2D       // Завантаження адреси 2D масиву
        lea edi, array1D       // Завантаження адреси 1D масиву
        mov ecx, totalElements // Загальна кількість елементів

        copy_loop :
        mov eax, [esi]         // Зчитати поточний елемент з 2D масиву
            mov[edi], eax         // Записати його у 1D масив
            add esi, 4             // Перейти до наступного елемента 2D масиву
            add edi, 4             // Перейти до наступного елемента 1D масиву
            loop copy_loop         // Повторити цикл
    }

    // Змінні для мінімуму та максимуму
    int minElement = INT_MAX;
    int maxElement = INT_MIN;

    // Знаходження мінімуму та максимуму у 1D масиві
    __asm {
        lea esi, array1D       // Завантаження адреси 1D масиву
        mov ecx, totalElements // Загальна кількість елементів
        mov eax, INT_MAX       // Початкове значення для мінімуму
        mov ebx, INT_MIN       // Початкове значення для максимуму

        find_loop :
        mov edx, [esi]         // Зчитати поточний елемент 1D масиву

            // Оновлення мінімального значення
            cmp edx, eax
            jge skip_min
            mov eax, edx

            skip_min :
        // Оновлення максимального значення
        cmp edx, ebx
            jle skip_max
            mov ebx, edx

            skip_max :
        add esi, 4             // Перейти до наступного елемента
            loop find_loop         // Повторити цикл

            mov minElement, eax    // Зберегти мінімальне значення
            mov maxElement, ebx    // Зберегти максимальне значення
    }

    // Виведення результату
    cout << "\nOne-dimensional array: " << endl;
    for (int i = 0; i < totalElements; i++) {
        cout << array1D[i] << " ";
    }
    cout << endl;

    cout << "\nMin value: " << minElement << endl;
    cout << "Max value: " << maxElement << endl;
    cout << "Sum: " << maxElement + minElement << endl;

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
