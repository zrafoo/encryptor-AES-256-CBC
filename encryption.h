#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#define BUFFER_SIZE 4096

/**
 * @brief Шифрует файл с использованием AES-256-CBC.
 *
 * @param input_file Путь к входному файлу.
 * @param output_file Путь к выходному файлу.
 * @param password Пароль для генерации ключа.
 */
void encrypt_file(const char *input_file, const char *output_file, const char *password);

#endif // ENCRYPTION_H
