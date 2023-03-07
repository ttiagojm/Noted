#include "daemon.h"
#include "config.h"
#include <stdio.h>

int main(int argc, char **argv){
    
    //TODO: Save the processes names in other place
    const char *pname = "onenote.exe";
    int pid, active;
    while(1){        
        pid = get_process_list(pname);

        if(pid > 0){
            printf("Process Name: %s\n", pname);
            printf("Process ID: %d\n", pid);
            active = is_active_page(pid);

            // Verify if the active is window 
            if(active == 0)
                printf("%d\n", active);
        }
        sleep(30);
    }

    return 0;
}