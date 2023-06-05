#include <windows.h>
#include <iostream>
int main()
{
    HANDLE hStopEvent = CreateEvent(NULL,
        TRUE,
        FALSE,
        L"Stop");
    SetEvent(hStopEvent);
    std::cout << "OS13_START stopped" << std::endl;
}