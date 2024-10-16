#include "keygen.h"
#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>

/**
 * @file keygen.c
 * @brief Функции для генерации ключа и вектора инициализации.
 * 
 * Применение встроенной функции из библиотеки openssl для формирования ключа и вектора инициализации из пароля, соли и количества итераций.
 * https://docs.openssl.org/master/man3/PKCS5_PBKDF2_HMAC/
 */

/**
 * @brief Функция генерирует ключ и вектор инициализации на основе пароля, соли и количества итераций.
 *
 * @param password Пароль для генерации ключа.
 * @param salt Соль для генерации ключа.
 * @param key Буфер для хранения ключа.
 * @param iv Буфер для хранения вектора инициализации.
 */
void generate_key_iv(const char *password, unsigned char *salt, unsigned char *key, unsigned char *iv) {
    const int iterations = 10000;
    unsigned char derived_key[KEY_SIZE + IV_SIZE]; // запишем ключ и вектор инициализации в derived_key

    if (!PKCS5_PBKDF2_HMAC(password, strlen(password), salt, SALT_SIZE, iterations, EVP_sha256(), sizeof(derived_key), derived_key)) {
        fprintf(stderr, "Ошибка генерации ключа.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(key, derived_key, KEY_SIZE);
    memcpy(iv, derived_key + KEY_SIZE, IV_SIZE);
}
