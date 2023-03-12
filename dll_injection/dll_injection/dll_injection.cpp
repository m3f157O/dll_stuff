// dll_injection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<windows.h>
#include<libloaderapi.h>
int main()
{

    LPCSTR path = "C:\\Users\\gigi_victim\\source\\repos\\dll_dummy\\x64\\Debug\\dll_dummy.dll";
    LPSTARTUPINFOA si = new STARTUPINFOA();
    PPROCESS_INFORMATION pi = new PROCESS_INFORMATION();

    if (CreateProcessA(NULL, (LPSTR)"notepad", NULL, NULL, TRUE, 0, NULL, NULL, si, pi) == NULL)
    {
        printf("[!] Failed to create process!\n");
        return 0;
    }
    else
    {
        printf("  :: Process ID: %d\n", pi->dwProcessId);
        printf("  :: Process Handle: %p\n", pi->hProcess);

        int len = strlen(path);

        LPVOID pAddress = VirtualAllocEx(pi->hProcess, nullptr, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        printf("  :: Base Address: %p\n", pAddress);
        WriteProcessMemory(pi->hProcess, pAddress, (LPVOID)path, len, NULL);
        PTHREAD_START_ROUTINE pRoutine = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32"), "LoadLibraryA");
        printf("  :: THREAD_START_ROUTINE: %p\n", pRoutine);
        HANDLE hThread = CreateRemoteThread(pi->hProcess, NULL, 0, pRoutine, pAddress, 0, NULL);
        printf("  :: Thread: %p\n", hThread);
        if (pi->hProcess)CloseHandle(pi->hProcess);
        if (pi->hThread)CloseHandle(pi->hThread);
        if (hThread)CloseHandle(hThread);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
