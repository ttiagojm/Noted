#include "daemon.h"
#include "config.h"
#include <stdio.h>

int main(int argc, char **argv){
    int pid, active;

    // Daemon loop; TODO: Create forks for each program to monitor
    while(1){        
        
        // Get process ID
        pid = get_process_list(programs[0]);

        // If the process was found
        if(pid > 0){
            active = is_active_window(pid);
        }

        sleep(30);
    }

    return 0;
}