#include "decryption.h"
#include "keygen.h"
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file decryption.c
 * @brief Функция, вызываемая для расшифровки файлов.
 */

/**
 * @brief Функция расшифровки файла.
 *
 * Расшифровывает зашифрованный файл и сохраняет результат в выходной файл.
 *
 * Используется структура данных EVP_CIPHER_CTX
 * https://docs.openssl.org/3.2/man3/EVP_EncryptInit/
 * @param input_file Путь к входному файлу.
 * @param output_file Путь к выходному файлу.
 * @param password Пароль для расшифровки.
 */
void decrypt_file(const char *input_file, const char *output_file, const char *password) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");
    if (!in || !out) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    unsigned char salt[SALT_SIZE];
    unsigned char key[KEY_SIZE], iv[IV_SIZE];

    fread(salt, 1, SALT_SIZE, in);  // Чтение соли из файла
    generate_key_iv(password, salt, key, iv);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, 0)) { // инициализация контекста под  AES-256-CBC
        fprintf(stderr, "Ошибка инициализации расшифровки.\n");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[BUFFER_SIZE];
    unsigned char out_buffer[BUFFER_SIZE + EVP_CIPHER_block_size(EVP_aes_256_cbc())];
    int len, out_len;

    while ((len = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        if (!EVP_CipherUpdate(ctx, out_buffer, &out_len, buffer, len)) { // расшифрование
            fprintf(stderr, "Ошибка во время расшифровки.\n");
            exit(EXIT_FAILURE);
        }
        fwrite(out_buffer, 1, out_len, out);
    }

    if (!EVP_CipherFinal_ex(ctx, out_buffer, &out_len)) {// выравнивание данных (padding)
        fprintf(stderr, "Ошибка завершения расшифровки.\n");
        exit(EXIT_FAILURE);
    }
    fwrite(out_buffer, 1, out_len, out);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in);
    fclose(out);
}
