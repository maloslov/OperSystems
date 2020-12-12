// OS1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <Windows.h>
#include <WinBase.h>
#include <iostream>

using namespace std;

string getPCName() {
    char name1[20];
    DWORD nSize = sizeof(name1);
    GetComputerNameA(name1, &nSize);
    return name1;
}
string getUsername() {
    char name2[20];
    DWORD nSize = sizeof(name2);
    GetUserNameA(name2, &nSize);
    return name2;
}

/*
OSVERSIONINFOW getVOS() {
    OSVERSIONINFOW osvi;
    //VerifyVersionInfo();
    //memset(&osvi, 0, sizeof(OSVERSIONINFOW));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
    //GetVersionExW(&osvi);
    return osvi;
}
*/

string getSysDir() {
    char path[50];
    int size = sizeof(path);
    GetSystemDirectoryA(path, size);
    return path;
}
string getWinDir() {
    char path[50];
    int size = sizeof(path);
    GetWindowsDirectoryA(path, size);
    return path;
}
string getTPath() {
    char path[50];
    int size = sizeof(path);
    GetTempPathA(size, path);
    return path;
}



int main()
{
    cout << "[SUBJECT:] Operating systems\n" <<
        "[LABWORK:] L1 - System information functions" << endl;
    //part 1 - computername & username
    cout << "\nCurrent computer name is " << getPCName() << endl;
    cout << "Current user name is " << getUsername() << endl;
    
    //part 2 - Sys directories
    cout << "\nSWT Directories:\n" << getSysDir() << endl <<
        getWinDir() << endl << getTPath() << endl;

    //part 3 - OS Version
    /*
    OSVERSIONINFOW osvi = getVOS();
    cout << "Version OS is " << osvi.dwPlatformId << "|" <<
        osvi.dwMajorVersion << "|" << osvi.dwMinorVersion << "|" <<
        osvi.dwBuildNumber << endl;
    */

    //part 4 - sys metrics
    cout << "\nDisplay size: " << GetSystemMetrics(0) << " x "
        << GetSystemMetrics(1) << endl;
    cout << "Mouse buttons: " << GetSystemMetrics(43) << endl;

    //part 5 - sys parameters
    int param[3];
    int fh,fw;
    SystemParametersInfoA(SPI_GETMOUSE, 0, &param, 0);
    cout << "\nSPI_GETMOUSE: " << param[0] <<"|"<<param[1]<<"|"<< param[2] << endl;
    SystemParametersInfoA(SPI_GETFOCUSBORDERHEIGHT, 0, &fh, 0);
    cout << "GETFOCUSBORDERHEIGHT: " << fh << endl;
    SystemParametersInfoA(SPI_GETFOCUSBORDERWIDTH, 0, &fw, 0);
    cout << "GETFOCUSBORDERWIDTH: " << fw << endl;

    //part 6 - sys colors


    //part 7 - time functions


    //part 8 - the others
    

    //end

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
