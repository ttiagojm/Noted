#include "daemon.h"
#include <stdio.h>

int main(int argc, char **argv){
    
    // TODO: Save the processes names in other place
    const char *pname = "onenote.exe";

    int pid = get_process_list(pname);

    if(pid > 0){
        printf("Process Name: %s\n", pname);
        printf("Process ID: %d\n", pid);
    }
    
    return 0;
}