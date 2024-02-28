#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hSerial;
int readComPorts() {
    SetConsoleOutputCP(1251);

    int Wait = 1;
    LPCTSTR sPortName1 = L"COM1";
    LPCTSTR sPortName2 = L"COM2";
    LPCTSTR sPortName3 = L"COM3";
    LPCTSTR sPortName4 = L"COM4";
    LPCTSTR sPortName5 = L"COM5";
    LPCTSTR sPortName6 = L"COM6";
    LPCTSTR sPortName7 = L"COM7";
    LPCTSTR sPortName8 = L"COM8";
    LPCTSTR sPortName9 = L"COM9";
    LPCTSTR sPortName10 = L"COM10";

    LPCTSTR sPortName_ar[10] = {
        sPortName1, sPortName2, sPortName3, sPortName4, sPortName5,
        sPortName6, sPortName7, sPortName8, sPortName9, sPortName10
    };

    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    // Открываем COM-порт
    //for (int i = 0; i< 10; i++) {
    hSerial = CreateFile(sPortName_ar[2], GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            cout << "COM порт не найден!" << std::endl;
        }
        else {
            cout << "Ошибка открытия COM порта!" << std::endl;
        }
    }
    else {
        cout << "Порт " << "COM3" << " был прочитан" << endl;
    }


    //}


    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "Ошибка получения параметров порта!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200;;  // Устанавливаем скорость передачи
    dcbSerialParams.ByteSize = 8;         // Устанавливаем количество бит данных
    dcbSerialParams.StopBits = ONESTOPBIT; // Устанавливаем количество стоп-бит
    dcbSerialParams.Parity = NOPARITY;     // Отключаем проверку четности

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "Ошибка установки параметров порта!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Устанавливаем таймауты
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    // Чтение данных
    while (1) {
        char data;
        DWORD bytesRead;
        if (ReadFile(hSerial, &data, sizeof(data), &bytesRead, NULL)) {
            std::cout << data;
           
            // Делаем что-то с прочитанными данными
        }
        else {
            std::cout << "Ошибка чтения данных с порта!" << std::endl;
            CloseHandle(hSerial); // Закрываем COM-порт
            return 0;
        }
    }



}

void writeToCOMPort(const char* portName, const char* data) {
    SetConsoleOutputCP(1251);

    LPCTSTR sPortName = TEXT("COM6");

    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    // Открываем COM-порт
    hSerial = CreateFile(sPortName, GENERIC_WRITE | GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            cout << "COM порт не найден!" << std::endl;
        }
        else {
            cout << "Ошибка открытия COM порта!" << std::endl;
        }
    }
    else {
        cout << "Порт " << "COM6" << " был прочитан" << endl;
    }


    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "Ошибка получения параметров порта!" << std::endl;
        CloseHandle(hSerial);
        return;
    }

    dcbSerialParams.BaudRate = CBR_115200;;  // Устанавливаем скорость передачи
    dcbSerialParams.ByteSize = 8;         // Устанавливаем количество бит данных
    dcbSerialParams.StopBits = ONESTOPBIT; // Устанавливаем количество стоп-бит
    dcbSerialParams.Parity = NOPARITY;     // Отключаем проверку четности

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "Ошибка установки параметров порта!" << std::endl;
        CloseHandle(hSerial);
        return;
    }

     //Устанавливаем таймауты
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    DWORD bytesWritten;
    if (!WriteFile(hSerial, data, strlen(data), &bytesWritten, NULL)) {
        std::cerr << "Ошибка записи в COM порт" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    else {
        std::cout << "Данные успешно отправлены в COM порт" << std::endl;
    }
    
    Sleep(100);

    char receivedData[2];
    DWORD bytesRead;
    if (ReadFile(hSerial, &receivedData, sizeof(receivedData), &bytesRead, NULL)) {
        cout << "Прочитано: " << receivedData << endl;
        // Делаем что-то с прочитанными данными
    }
    else {
        cout << "Ошибка чтения данных с порта!" << endl;
    }


    

    CloseHandle(hSerial);
}

