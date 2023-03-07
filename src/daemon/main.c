#include "daemon.h"
#include "config.h"
#include <stdio.h>

int main(int argc, char **argv){
    int active;

    // Daemon loop; TODO: Create forks for each program to monitor
    while(1){        
        
        // Get process ID
        programs[0].pid = get_process_list(programs[0].name);

        // If the process was found
        if(programs[0].pid > 0){
            active = is_active_window(programs[0].pid);
        }

        sleep(30);
    }

    return 0;
}