#include <iostream>
#include <random>
#include <ctime>
 
using namespace std;
 
extern "C"{
 
    int sum = 0;
 
    const int size = 3;
    int tempSize = size;
    int multiplierMainDiagonal = size * 4 + 4;
    int multiplierSaidDiagonal = size * 4 - 4;
 
    int array[size][size];
};
 
int main()
{
    srand(time(0));
 
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            array[i][j] = 0 + rand() % 10;
        }
    }
 
    __asm
     (
     R"(
       .intel_syntax noprefix
    ;//{
        mov eax, 0              ;// этот регистр будет хранить сумму элементов двух диагоналей
        mov ecx, 0              ;// этот регистр будет указывать адрес элементов на диагоналях
        mov ebx, 0              ;// этот регистр считает количество пройденных элементов на побочной диагонали
        mov edx, 0              ;// этот регистр считает количетсво пройденных элементов на главной диагонали
        jmp Main
 
            StartNewDiagonal:
        mov ecx, multiplierSaidDiagonal
 
            Main:
        add eax, array[ecx]         
        cmp edx, tempSize
        jl Incrementing1
        jmp Incrementing2
 
            Incrementing1:
        add ecx, multiplierMainDiagonal
        add edx, 1
        jmp CheckDiagonal
 
            Incrementing2:
        add ecx, multiplierSaidDiagonal
        add ebx, 1
 
            CheckDiagonal:
        cmp edx, tempSize
        jl Main
        cmp ebx, 0
        je StartNewDiagonal
        cmp ebx, tempSize
        jl Main
 
            mov sum, eax
    ;//}
        .att_syntax
    )"
    );
 
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
 
    if (size % 2 == 1) 
    {
        sum -= array[size / 2][size / 2];
    }
    cout << "Sum of diagonal elements = " << sum;
 
    return 0;
}
