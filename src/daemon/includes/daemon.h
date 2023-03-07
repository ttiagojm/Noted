#ifndef DAEMON_H
#define DAEMON_H

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <unistd.h>
#include <time.h>

// Time to sleep between verifications
#define SLEEP_TIME 10       

// Type definitions
typedef struct Counter{
    time_t prev_time;
    time_t cur_time;
} counter_t;

typedef struct Program{
    char name[50];
    int pid;
    counter_t timer;
} program_t;


// Prototyped functions
int get_process_list(const char *pname);
int is_active_window(int pid);
void update_timer(counter_t *counter);
void clear_timer(counter_t *counter);

// Static variables
static program_t programs[] = {
    {"OneNote.exe", -1, {0}}

};

#endif