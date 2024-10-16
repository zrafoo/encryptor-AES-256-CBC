#include "encryption.h"
#include "keygen.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file encryption.c
 * @brief Функция, вызываемая для шифрования файлов.
 */

/**
 * @brief Функция шифрования файла.
 *
 * Шифрует входной файл и сохраняет результат в выходной файл, при этом соль записывается в начало файла.
 *
 * @param input_file Путь к входному файлу.
 * @param output_file Путь к выходному файлу.
 * @param password Пароль для шифрования.
 */
void encrypt_file(const char *input_file, const char *output_file, const char *password) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");
    if (!in || !out) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    unsigned char salt[SALT_SIZE];
    unsigned char key[KEY_SIZE], iv[IV_SIZE];

    if (!RAND_bytes(salt, SALT_SIZE)) {
        fprintf(stderr, "Ошибка генерации соли.\n");
        exit(EXIT_FAILURE);
    }
    fwrite(salt, 1, SALT_SIZE, out);  // Записываем соль в файл

    generate_key_iv(password, salt, key, iv);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, 1)) {// инициализация контекста под  AES-256-CBC
        fprintf(stderr, "Ошибка инициализации шифрования.\n");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[BUFFER_SIZE];
    unsigned char out_buffer[BUFFER_SIZE + EVP_CIPHER_block_size(EVP_aes_256_cbc())];
    int len, out_len;

    while ((len = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        if (!EVP_CipherUpdate(ctx, out_buffer, &out_len, buffer, len)) { // шифрование
            fprintf(stderr, "Ошибка во время шифрования.\n");
            exit(EXIT_FAILURE);
        }
        fwrite(out_buffer, 1, out_len, out);
    }

    if (!EVP_CipherFinal_ex(ctx, out_buffer, &out_len)) { // выравнивание данных (padding)
        fprintf(stderr, "Ошибка завершения шифрования.\n");
        exit(EXIT_FAILURE);
    }
    fwrite(out_buffer, 1, out_len, out);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in);
    fclose(out);
}
