// Monitor.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>
#include <psapi.h>
#include <shellapi.h>
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shell32.lib")

int __ProcessMonitor()
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
    while (true)
    {
		if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
			return EXIT_FAILURE;
     
		cProcesses = cbNeeded / sizeof(DWORD);
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        TCHAR szFilePath[MAX_PATH] = TEXT("<unknown>");
       
        for ( i = 0; i < cProcesses; i++ ) {
            DWORD processID = aProcesses[i];
            HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                PROCESS_VM_READ,
                FALSE, processID );
          
            if (NULL != hProcess ) {
                HMODULE hMod;
                DWORD cbNeeded;
                if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                    &cbNeeded) ) {
                    GetModuleBaseName( hProcess, hMod, szProcessName,
                        sizeof(szProcessName)/sizeof(TCHAR) );
                    GetModuleFileName(hMod, szFilePath,
                        sizeof(szFilePath)/sizeof(TCHAR));
                }
            }
          
            //_tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );
            if (_tcscmp(szProcessName, TEXT("PC2-03-30.exe")) == 0)
            {
                Sleep(1000); 
                CloseHandle(hProcess);
                break;
            }
            CloseHandle( hProcess );
        }
        _stprintf(szFilePath, TEXT("E:\\code\\github\\PC2CPP\\Release\\PC2-03-30.exe"));
        if (i == cProcesses)
            ShellExecute(NULL,TEXT("open"),szFilePath,NULL,NULL,SW_SHOW);   
		Sleep(1000);
    }
    //system("PAUSE");
    return EXIT_SUCCESS;
}

int _tmain(int argc, _TCHAR* argv[])
{
	__ProcessMonitor();
	return 0;
}

