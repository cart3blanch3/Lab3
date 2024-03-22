#include <windows.h>           
#include <iostream>            
#include <sstream>             

int main() {                  
    HANDLE hPipe;  // Объявление дескриптора именованного канала
    char buffer[100]; // Объявление буфера для чтения сообщений из канала

    hPipe = CreateNamedPipe( // Создание именованного канала
        L"\\\\.\\pipe\\MyPipe",              // Имя канала
        PIPE_ACCESS_OUTBOUND,                // Режим доступа (только для записи)
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // Тип сообщений, режим чтения сообщений и ожидание
        1,                                   // Количество экземпляров канала
        0, 0, 0, NULL);                      // Дополнительные параметры, установлены по умолчанию

    ConnectNamedPipe(hPipe, NULL); // Ожидание подключения клиента к каналу

    for (int i = 0; i < 10; i++) { // Цикл для записи сообщений в канал 10 раз
        // Формирование сообщения с номером итерации
        std::stringstream ss; // Создание потока строк
        ss << "Hello " << i; // Запись сообщения в поток
        std::string message = ss.str(); // Получение строки из потока

        // Запись сообщения в канал
        WriteFile(hPipe, message.c_str(), message.size() + 1, NULL, NULL); // Запись сообщения в канал
        Sleep(2000); // Пауза в 2 секунды перед следующей итерацией
    }

    // Ожидание завершения операций ввода-вывода и сброс буферов
    FlushFileBuffers(hPipe); // Сброс буферов записи данных в именованный канал
    DisconnectNamedPipe(hPipe); // Отключение канала
    CloseHandle(hPipe); // Закрытие дескриптора канала

    return 0;
}