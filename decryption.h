#ifndef DECRYPTION_H
#define DECRYPTION_H

#define BUFFER_SIZE 4096

/**
 * @brief Расшифровывает файл, зашифрованный с использованием AES-256-CBC.
 *
 * @param input_file Путь к зашифрованному файлу.
 * @param output_file Путь к расшифрованному файлу.
 * @param password Пароль для генерации ключа.
 */
void decrypt_file(const char *input_file, const char *output_file, const char *password);

#endif // DECRYPTION_H
