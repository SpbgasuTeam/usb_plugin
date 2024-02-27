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

    // ��������� COM-����
    //for (int i = 0; i< 10; i++) {
    hSerial = CreateFile(L"COM3", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            cout << "COM ���� �� ������!" << std::endl;
        }
        else {
            cout << "������ �������� COM �����!" << std::endl;
        }
    }
    else {
        cout << "���� " << "COM3" << " ��� ��������" << endl;
        Wait = 0;
    }


    //}


    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "������ ��������� ���������� �����!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200;;  // ������������� �������� ��������
    dcbSerialParams.ByteSize = 8;         // ������������� ���������� ��� ������
    dcbSerialParams.StopBits = ONESTOPBIT; // ������������� ���������� ����-���
    dcbSerialParams.Parity = NOPARITY;     // ��������� �������� ��������

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "������ ��������� ���������� �����!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // ������������� ��������
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    // ������ ������
    while (1) {
        char data;
        DWORD bytesRead;
        if (ReadFile(hSerial, &data, sizeof(data), &bytesRead, NULL)) {
            std::cout << data;
           
            // ������ ���-�� � ������������ �������
        }
        else {
            std::cout << "������ ������ ������ � �����!" << std::endl;
            CloseHandle(hSerial); // ��������� COM-����
            return 0;
        }
    }



}
