#include <windows.h>           
#include <iostream>            
#include <sstream>             

int main() {                  
    HANDLE hPipe;  // ���������� ����������� ������������ ������
    char buffer[100]; // ���������� ������ ��� ������ ��������� �� ������

    hPipe = CreateNamedPipe( // �������� ������������ ������
        L"\\\\.\\pipe\\MyPipe",              // ��� ������
        PIPE_ACCESS_OUTBOUND,                // ����� ������� (������ ��� ������)
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // ��� ���������, ����� ������ ��������� � ��������
        1,                                   // ���������� ����������� ������
        0, 0, 0, NULL);                      // �������������� ���������, ����������� �� ���������

    ConnectNamedPipe(hPipe, NULL); // �������� ����������� ������� � ������

    for (int i = 0; i < 10; i++) { // ���� ��� ������ ��������� � ����� 10 ���
        // ������������ ��������� � ������� ��������
        std::stringstream ss; // �������� ������ �����
        ss << "Hello " << i; // ������ ��������� � �����
        std::string message = ss.str(); // ��������� ������ �� ������

        // ������ ��������� � �����
        WriteFile(hPipe, message.c_str(), message.size() + 1, NULL, NULL); // ������ ��������� � �����
        Sleep(2000); // ����� � 2 ������� ����� ��������� ���������
    }

    // �������� ���������� �������� �����-������ � ����� �������
    FlushFileBuffers(hPipe); // ����� ������� ������ ������ � ����������� �����
    DisconnectNamedPipe(hPipe); // ���������� ������
    CloseHandle(hPipe); // �������� ����������� ������

    return 0;
}