/**
 * @file input.cpp
 * @brief Реализация класса Input для обработки пользовательского ввода.
 */
#include "../../include/game/input.h"

/**
 * @brief Статический буфер для хранения одного символа ввода.
 *
 * Используется для временного хранения символа, если он был прочитан, но еще не обработан.
 */
char Input::inputBuffer = 0;

/**
 * @brief Конструктор класса Input.
 */
Input::Input() {}

/**
 * @brief Деструктор класса Input.
 */
Input::~Input() {}

/**
 * @brief Проверяет, есть ли доступный пользовательский ввод.
 *
 * @return true, если есть доступный ввод, иначе false.
 */
bool Input::hasInput() const {
    if (inputBuffer != 0) {
        return true;
    }
    
    char ch;
    ssize_t bytesRead = read(STDIN_FILENO, &ch, 1);
    
    if (bytesRead > 0) {
        inputBuffer = ch;
        return true;
    }
    
    return false;
}

/**
 * @brief Считывает один символ пользовательского ввода.
 *
 * @return Прочитанный символ или 0, если ввод недоступен.
 */
char Input::getChar() const {
    if (inputBuffer != 0) {
        char tmp = inputBuffer;
        inputBuffer = 0;
        return tmp;
    }
    
    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return ch;
    }
    
    return 0;
}

/**
 * @brief Считывает несколько символов пользовательского ввода в буфер.
 *
 * @param buffer Указатель на буфер для сохранения ввода.
 * @param bufferSize Размер буфера.
 * @return Количество прочитанных байт или 0, если ввод недоступен.
 */
int Input::readInput(char* buffer, int bufferSize) const {
    if (inputBuffer != 0 && bufferSize > 0) {
        buffer[0] = inputBuffer;
        inputBuffer = 0;
        
        if (bufferSize > 1) {
            ssize_t bytesRead = read(STDIN_FILENO, buffer + 1, bufferSize - 1);
            return (bytesRead > 0) ? bytesRead + 1 : 1;
        }
        return 1;
    }
    
    ssize_t bytesRead = read(STDIN_FILENO, buffer, bufferSize);
    return bytesRead > 0 ? bytesRead : 0;
}