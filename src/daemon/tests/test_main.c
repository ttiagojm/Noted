#include "config.h"
#include "daemon.h"
#include <stdio.h>
#include <assert.h>
#include <windows.h>

int test_programs_array(){
    int size = sizeof(programs) / sizeof(programs[0]);
    assert(size == 1);

    return 0;
}

int test_find_pid(){
    int size = sizeof(programs) / sizeof(programs[0]);
    int pid, i;
    char cmd[50];
    
    for(i = 0; i < size; i++){
        memset(cmd, 0, 50);

        sprintf(cmd, "start %s", programs[i]);   
        system(cmd);

        // Check if the process exists
        pid = get_process_list(programs[i]);
        assert(pid > 0);

        // Kill program
        memset(cmd, 0, 50);
        sprintf(cmd, "taskkill /PID %d /F", pid);
        system(cmd); 

         // Check if the process exists
        pid = get_process_list(programs[i]);
        assert(pid == -1);
    }

    return 0;
}

int main(int argc, char **argv){
    int ret;
    
    ret = test_programs_array();
    
    if(ret == 0)
        printf("[+] SUCCESS on verify wanted programs!\n");

    ret = test_find_pid();

    if(ret == 0)
        printf("[+] SUCCESS on detecting programs!\n");
    return 0;
}