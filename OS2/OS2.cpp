#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <shlwapi.h>
#include <tlhelp32.h>
#include <fstream>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")

void getFromHandle(HMODULE handle) {
    wchar_t path[80]; // создаем массив для записи пути
    wstring name; // создаем строку для записи названия процесса
    GetModuleFileName(handle, path, 80); // получает полный путь к файлу, содержащему указанный модуль
    wcout << "Descriptor: " << handle << "\nName: " << name << "\nFullname: " << path << endl;
}

void getFromName(wchar_t* name) {
    HMODULE handle = GetModuleHandle(name); // возвращает хэндл текущего исполнимого модуля
    wchar_t path[80]; // создаем массив для записи пути
    GetModuleFileName(handle, path, 80); // получает полный путь к файлу, содержащему указанный модуль
    wcout << "Descriptor: " << handle << "\nName: " << name << "\nFullname: " << path << endl;
}

void getFromPath(wchar_t* path) {
    HANDLE handle;
    wchar_t name[80];
    wcscpy(name, PathFindFileName(path));
    handle = GetModuleHandle(name);
    wcout << "Descriptor: " << handle << "\nName: " << name << "\nFullname: " << path << endl;
}

void getCurProcInfo() {
    HMODULE handle = GetModuleHandle(NULL); // возвращает хэндл текущего исполнимого модуля
    wchar_t path[80]; // создаем массив для записи пути
    wstring name; // создаем строку для записи названия процесса
    GetModuleFileName(handle, path, 80); // получает полный путь к файлу, содержащему указанный модуль
    wcout << "Descriptor: " << handle << "\nName: " << name << "\nFullname: " << path << endl;
}

int main()
{
    setlocale(LC_ALL,"RUSSIAN");

#pragma region part1

    // Принимая дескриптор, имя и полное имя модуля - возвращаем два элемента в выходных параметрах

    cout << "Часть 1\r\n\tДля библиотеки:" << endl;
    getFromName((wchar_t*)L"kernel32.dll");
    getFromHandle((HMODULE)0x75E40000);
    getFromPath((wchar_t*)L"C:\\Windows\\system32\\kernel32.dll");

    cout << "\r\n\tДля приложения:" << endl;
    getFromName((wchar_t*)L"OS2.exe");
    getFromPath((wchar_t*)L"C:\\Users\\Maloslov\\source\\repos\\OperShop\\Debug\\OS2.exe");
    getCurProcInfo();
#pragma endregion
#pragma region part2
    cout << "\r\n\r\nЧасть 2\r\n" << endl;
    DWORD procID = GetCurrentProcessId(); // Создаем для записи для идентификатора процесса
    HANDLE handle = GetCurrentProcess(); // Создаем для записи псевдодескриптора процесса
    HANDLE dHandle, openProcess; // Создаем для записи дескриптора текущего процесса

    if (!DuplicateHandle(GetCurrentProcess(), handle, GetCurrentProcess(), 
        &dHandle, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        cout << "Ошибка копирования!" << endl;
    }

    openProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, procID); // определяем копию дескриптора текущего процесса
    cout << "ID текущего процесса: " << procID << "\nПсевдодескриптор: " << handle << "\r\n" 
        << "Дескриптор DuplicateHandle: " << dHandle << "\nДескриптор OpenProcess: " << openProcess << endl;

    CloseHandle(dHandle);
    CloseHandle(openProcess);

#pragma endregion
#pragma region part3
    // Выдает список перечисления всех процессов, потоков, модулей и их свойства в системе
    HANDLE hSnapProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    HANDLE hSnapModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
    HANDLE hSnapThread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    PROCESSENTRY32 pEntry = {};
    pEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapProcess, &pEntry);
    cout << "Часть 3\r\n\tПРОЦЕССЫ\r\nПотоки\tМодуль" << endl;
    wcout << pEntry.cntThreads << "\t" << pEntry.szExeFile << endl;

    while (Process32Next(hSnapProcess, &pEntry)) {
        wcout << pEntry.cntThreads << "\t" << pEntry.szExeFile << endl;
    }

    THREADENTRY32 threadEntry = {};
    threadEntry.dwSize = sizeof(THREADENTRY32);
    Thread32First(hSnapThread, &threadEntry);

    cout << "\r\n\tПОТОКИ\r\nID потока: " << "\tID владельца:\r\n" << endl;
    wcout << threadEntry.th32ThreadID << "\t" << threadEntry.th32OwnerProcessID << endl;

    while (Thread32Next(hSnapThread, &threadEntry)) {
        wcout << threadEntry.th32ThreadID << "\t" << threadEntry.th32OwnerProcessID << endl;
    }

    MODULEENTRY32 modEntry = {};
    modEntry.dwSize = sizeof(MODULEENTRY32);
    Module32First(hSnapModule, &modEntry);
    cout << "\r\n\tМОДУЛИ" << endl; 
    wcout << modEntry.szModule << endl;

    while (Module32Next(hSnapModule, &modEntry)) {
        wcout << modEntry.szModule << endl;
    }

    CloseHandle(hSnapProcess);
    CloseHandle(hSnapModule);
    CloseHandle(hSnapThread);
#pragma endregion
}
