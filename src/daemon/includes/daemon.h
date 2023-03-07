#ifndef DAEMON_H
#define DAEMON_H

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

int get_process_list(const char *pname);

#endif