#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contract.h"

int main() {
    char command[256];
    
    printf("Программа со статическим связыванием (использует реализацию 1)\n");
    printf("Команды:\n");
    printf("  0 - выход из программы\n");
    printf("  1 K - вычислить Pi с точностью K членов ряда\n");
    printf("  2 x - перевести число x в двоичную систему\n");
    printf("Пример: 1 1000\n");
    
    while (1) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        
        if (command[0] == '0') {
            break;
        }
        else if (command[0] == '1') {
            int K;
            if (sscanf(command + 1, "%d", &K) == 1) {
                float result = Pi(K);
                printf("Pi(%d) = %f\n", K, result);
            } else {
                printf("Ошибка: неверный формат команды. Используйте: 1 K\n");
            }
        }
        else if (command[0] == '2') {
            long long x;
            if (sscanf(command + 1, "%lld", &x) == 1) {
                char* result = translation(x);
                printf("translation(%lld) = %s\n", x, result);
                free(result); // Не забываем освободить память
            } else {
                printf("Ошибка: неверный формат команды. Используйте: 2 x\n");
            }
        }
        else {
            printf("Неизвестная команда\n");
        }
    }
    
    return 0;
}