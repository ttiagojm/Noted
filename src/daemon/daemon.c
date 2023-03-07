#include "daemon.h"

int get_process_list(const char *pname){
    /*
        Function constructed from: https://learn.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
    */

    // Resource managed by Win. Kernel (in this case, System's processes snapshot)
    HANDLE hProcessSnap;

    // Struct to save process informations
    PROCESSENTRY32 pe32;

    // Save snapshot from system's processes
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE ){
        _tprintf( TEXT("Can't make a snapshot\n"));
        return -2;
    }

    pe32.dwSize = sizeof( PROCESSENTRY32 );

    // Try to get the first process and save it into pe32
    if( !Process32First( hProcessSnap, &pe32 ) ){
        _tprintf( TEXT("Can't get first process\n"));
        CloseHandle( hProcessSnap );
        return -3;
    }


    // Got the first, loop through the remaining
    do{

        if(stricmp(pname, pe32.szExeFile) == 0){
            return pe32.th32ProcessID;
        }

        // _tprintf(TEXT("%s\n"), pe32.szExeFile);
        // _tprintf(TEXT("%s\n"), pname);

    } while( Process32Next( hProcessSnap, &pe32 ) );

    CloseHandle( hProcessSnap );

    _tprintf( TEXT("Couldn't get the process\n"));

    return -1;
}