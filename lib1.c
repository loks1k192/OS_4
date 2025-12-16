#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contract.h"

// Реализация 1 для Pi: Ряд Лейбница
float Pi(int K) {
    float pi = 0.0;
    int sign = 1;
    
    for (int i = 0; i < K; i++) {
        pi += sign * (4.0 / (2 * i + 1));
        sign = -sign;
    }
    
    return pi;
}

// Реализация 1 для translation: в двоичную систему
char* translation(long x) {
    // Определяем максимальную длину двоичного представления
    int max_len = sizeof(long) * 8 + 1; // +1 для знака и завершающего нуля
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
    
    // Преобразуем в двоичную систему
    int index = 0;
    while (num > 0) {
        result[index++] = (num % 2) + '0';
        num /= 2;
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