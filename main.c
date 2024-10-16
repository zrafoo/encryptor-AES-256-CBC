#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "encryption.h"
#include "decryption.h"
#include <time.h>

/**
 * @file main.c
 * @brief main файл программы для шифрования/расшифровки файлов.
 */

/**
 * @brief Основная функция программы.
 *
 * Программа принимает аргументы командной строки для шифрования или расшифровки файлов с использованием пароля.
 */
int main(int argc, char *argv[]) {
    int opt;
    int mode = 0;  // флаг режима - 0 режим шифрования, 1 режим расшифровки.
    char *input_file = NULL;
    char *output_file = NULL;
    char *password = NULL;
    clock_t start_time = clock();

    // Проверяем количество аргументов
    if (argc < 4 || argc > 5) {
        fprintf(stderr, "Usage: %s [-d to decrypt] input_file output_file password\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    // Проверка на ключ -d
    if (strcmp(argv[1], "-d") == 0) {
        mode = 1;
        input_file = argv[2];
        output_file = argv[3];
        password = argv[4];
    } else {
        input_file = argv[1];
        output_file = argv[2];
        password = argv[3];
    }

    // Выполняем шифрование или расшифровку
    if (mode) {
        decrypt_file(input_file, output_file, password);
    } else {
        encrypt_file(input_file, output_file, password);
    }
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken: %.2f sec.\n", elapsed_time);
    return 0;
}
