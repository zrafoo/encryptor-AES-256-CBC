#ifndef KEYGEN_H
#define KEYGEN_H

#define SALT_SIZE 16
#define KEY_SIZE 32
#define IV_SIZE 16

/**
 * @brief Функция генерирует ключ и вектор инициализации на основе пароля, соли и количества итераций.
 *
 * @param password Пароль для генерации ключа.
 * @param salt Соль для генерации ключа.
 * @param key Буфер для хранения ключа.
 * @param iv Буфер для хранения вектора инициализации.
 */
void generate_key_iv(const char *password, unsigned char *salt, unsigned char *key, unsigned char *iv);

#endif // KEYGEN_H
