#include <cstdio>
#include <string>
#include <windows.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::wstring szExePath = L".\\OS15_START.exe T:\\C3S2\\OS\\HTService\\HT\\test.ht";

    // Запуск внешней программы
    if (!CreateProcess(NULL, const_cast<LPWSTR>(szExePath.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Error CreateProcess: %d\n", GetLastError());
        return -1;
    }

    // Ожидание завершения работы процесса
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Закрытие дескрипторов процесса и потока
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
