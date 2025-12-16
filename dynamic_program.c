#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

// Определяем типы функций
typedef float (*PiFunc)(int);
typedef char* (*TranslationFunc)(long);

int main() {
    void *handle = NULL;
    PiFunc Pi = NULL;
    TranslationFunc translation = NULL;
    
    int current_lib = 1; // 1 - первая реализация, 2 - вторая
    char command[256];
    
    // Загружаем первую библиотеку по умолчанию
    handle = dlopen("./libcontract1.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки 1: %s\n", dlerror());
        return 1;
    }
    
    // Загружаем функции из первой библиотеки
    Pi = (PiFunc)dlsym(handle, "Pi");
    translation = (TranslationFunc)dlsym(handle, "translation");
    
    if (!Pi || !translation) {
        fprintf(stderr, "Ошибка загрузки функций: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    
    printf("Программа с динамической загрузкой библиотек\n");
    printf("Команды:\n");
    printf("  0 - переключить реализацию (сейчас: реализация %d)\n", current_lib);
    printf("  1 K - вычислить Pi с точностью K членов ряда\n");
    printf("  2 x - перевести число x в другую систему\n");
    printf("Пример: 1 1000\n");
    
    while (1) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        
        if (command[0] == '0') {
            // Переключаем библиотеку
            dlclose(handle);
            
            if (current_lib == 1) {
                handle = dlopen("./libcontract2.so", RTLD_LAZY);
                current_lib = 2;
                printf("Переключено на реализацию 2 (Формула Валлиса, троичная система)\n");
            } else {
                handle = dlopen("./libcontract1.so", RTLD_LAZY);
                current_lib = 1;
                printf("Переключено на реализацию 1 (Ряд Лейбница, двоичная система)\n");
            }
            
            if (!handle) {
                fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
                return 1;
            }
            
            // Загружаем функции из новой библиотеки
            Pi = (PiFunc)dlsym(handle, "Pi");
            translation = (TranslationFunc)dlsym(handle, "translation");
            
            if (!Pi || !translation) {
                fprintf(stderr, "Ошибка загрузки функций: %s\n", dlerror());
                dlclose(handle);
                return 1;
            }//1 1000
        }
        else if (command[0] == '1') {
            int K;
            if (sscanf(command + 1, "%d", &K) == 1) {
                float result = Pi(K);
                printf("Pi(%d) = %f (реализация %d)\n", K, result, current_lib);
            } else {
                printf("Ошибка: неверный формат команды. Используйте: 1 K\n");
            }
        }
        else if (command[0] == '2') {
            long x;
            if (sscanf(command + 1, "%ld", &x) == 1) {
                char* result = translation(x);
                printf("translation(%ld) = %s (реализация %d)\n", x, result, current_lib);
                free(result); // Не забываем освободить память
            } else {
                printf("Ошибка: неверный формат команды. Используйте: 2 x\n");
            }
        }
        else {
            printf("Неизвестная команда\n");
        }
    }
    
    dlclose(handle);
    return 0;
}