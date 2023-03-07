#ifndef DAEMON_H
#define DAEMON_H

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <unistd.h>

int get_process_list(const char *pname);
int is_active_page(int pid);

#endif