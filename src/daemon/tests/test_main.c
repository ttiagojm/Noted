#include "daemon.h"
#include "websocket.h"
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

        sprintf(cmd, "start %s", programs[i].name);   
        system(cmd);
        sleep(5);

        // Check if the process exists
        pid = get_process_list(programs[i].name);
        assert(pid > 0);

        // Kill program
        memset(cmd, 0, 50);
        sprintf(cmd, "taskkill /PID %d /F", pid);
        system(cmd); 
        sleep(5);

         // Check if the process exists
        pid = get_process_list(programs[i].name);
        assert(pid == -1);
    }

    return 0;
}

int test_is_active_window(){
    int pid, ret;
    int size = sizeof(programs) / sizeof(programs[0]);
    char cmd[50];
    HWND foreground;

    for(int i = 0; i < size; i++){
        memset(cmd, 0, 50);
        sprintf(cmd, "start %s", programs[i].name);
        system(cmd);
        memset(cmd, 0, 50);

        sleep(5);

        pid = get_process_list(programs[i].name);

        ret = is_active_window(pid);

        assert(ret == 0);

        // Kill program
        memset(cmd, 0, 50);
        sprintf(cmd, "taskkill /PID %d /F", pid);
        system(cmd);

    }  

    return 0;
}

int test_http_socket(const char* path_cacert){
    return make_api_request("https://noted-api.onrender.com/statistics", path_cacert);
}

int main(int argc, char **argv){
    int ret;

    // if(argc == 1){
    //     printf("[!] Forgot to pass the cacert path\n");
    //     return 1;
    // }
    
    // ret = test_programs_array();
    
    // if(ret == 0)
    //     printf("[+] SUCCESS on verify wanted programs!\n");

    // ret = test_find_pid();

    // if(ret == 0)
    //     printf("[+] SUCCESS on detecting programs!\n");

    // ret = test_is_active_window();

    // if(ret == 0)
    //     printf("[+] SUCCESS on detecting active window!\n");

    ret = test_http_socket(argv[1]);

    if(ret == 0)
        printf("[+] SUCCESS on sending through HTTP socket!\n");

    return 0;
}