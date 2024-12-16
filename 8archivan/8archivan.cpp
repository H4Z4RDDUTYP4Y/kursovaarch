// 8archivan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath> 
#include <iomanip> 
#include <climits>

using namespace std;

int main() {
    const int rows = 3;        // ʳ������ �����
    const int cols = 3;        // ʳ������ ��������
    int array2D[rows][cols] = {  // ���������� �����
        {3, 5, 2},
        {1, 9, 8},
        {6, 4, 7}
    };
    int array1D[rows * cols];  // ����������� ����� ��� ����������
    const int totalElements = rows * cols;

    // ��������� ����������� 2D ������
    cout << "Initial 2D array:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << array2D[i][j] << " ";
        }
        cout << endl;
    }

    // ������������ 2D ������ � 1D ����� ����� ��������
    __asm {
        lea esi, array2D       // ������������ ������ 2D ������
        lea edi, array1D       // ������������ ������ 1D ������
        mov ecx, totalElements // �������� ������� ��������

        copy_loop :
        mov eax, [esi]         // ������� �������� ������� � 2D ������
            mov[edi], eax         // �������� ���� � 1D �����
            add esi, 4             // ������� �� ���������� �������� 2D ������
            add edi, 4             // ������� �� ���������� �������� 1D ������
            loop copy_loop         // ��������� ����
    }

    // ���� ��� ������ �� ���������
    int minElement = INT_MAX;
    int maxElement = INT_MIN;

    // ����������� ������ �� ��������� � 1D �����
    __asm {
        lea esi, array1D       // ������������ ������ 1D ������
        mov ecx, totalElements // �������� ������� ��������
        mov eax, INT_MAX       // ��������� �������� ��� ������
        mov ebx, INT_MIN       // ��������� �������� ��� ���������

        find_loop :
        mov edx, [esi]         // ������� �������� ������� 1D ������

            // ��������� ���������� ��������
            cmp edx, eax
            jge skip_min
            mov eax, edx

            skip_min :
        // ��������� ������������� ��������
        cmp edx, ebx
            jle skip_max
            mov ebx, edx

            skip_max :
        add esi, 4             // ������� �� ���������� ��������
            loop find_loop         // ��������� ����

            mov minElement, eax    // �������� �������� ��������
            mov maxElement, ebx    // �������� ����������� ��������
    }

    // ��������� ����������
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
