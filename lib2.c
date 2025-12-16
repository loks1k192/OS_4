#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contract.h"

// Реализация 2 для Pi: Формула Валлиса
float Pi(int K) {
    float pi = 1.0;
    
    for (int i = 1; i <= K; i++) {
        float numerator = 4.0 * i * i;
        float denominator = 4.0 * i * i - 1.0;
        pi *= numerator / denominator;
    }
    
    return pi * 2.0;
}

// Реализация 2 для translation: в троичную систему
char* translation(long x) {
    // Определяем максимальную длину троичного представления
    int max_len = sizeof(long) * 8 + 2; // Более чем достаточно
    char* result = (char*)malloc(max_len * sizeof(char));
    
    if (x == 0) {
        strcpy(result, "0");
        return result;
    }
    
    // Работаем с положительным числом
    long num = x;
    if (x < 0) {
        num = -x;
    }
    
    // Преобразуем в троичную систему
    int index = 0;
    while (num > 0) {
        result[index++] = (num % 3) + '0';
        num /= 3;
    }
    
    // Добавляем знак минус если нужно
    if (x < 0) {
        result[index++] = '-';
    }
    
    result[index] = '\0';
    
    // Разворачиваем строку
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
    
    return result;
}