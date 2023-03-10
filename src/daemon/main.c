#include "daemon.h"
#include <stdio.h>

int main(int argc, char **argv){

    if(argc == 1){
        printf("[!] Forgot to pass the cacert path\n");
        return 1;
    }

    printf("%s\n", argv[1]);

    int active;

    // Daemon loop; TODO: Create forks for each program to monitor
    while(1){        
        
        // Get process ID
        programs[0].pid = get_process_list(programs[0].name);

        // If the process was found and the window is active: Count
        if(programs[0].pid > 0 && is_active_window(programs[0].pid) == 0){
            update_timer(&programs[0].timer);
            printf("%ld\n", programs[0].timer.cur_time);
        }
        else{
            printf("[!] Cleaning...");
            clear_timer(&programs[0].timer);
        }
        
        sleep(SLEEP_TIME);
    }

    return 0;
}