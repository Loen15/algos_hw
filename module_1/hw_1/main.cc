// Во всех задачах необходимо использование битовых операций.  
// Использование арифметических операций запрещено.  
// Входное число лежит в диапазоне 0..232 -1 и вводится в десятичном виде.  

// 1.1 Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях. Позиции битов нумеруются с 0.  

#include <iostream>

int BitCounter(unsigned int number); 

int main()
{
    // ввод
    unsigned int number;
    std::cin >> number;

    //вывод алгоритма
    std::cout << BitCounter(number) << std::endl;
    return 0;
}


int BitCounter(unsigned int number) {
    int count= 0;
    while (number > 0) {
        if (number & 1) {
            count++;
        }
        number = number >> 2;
    }
    return count;
}