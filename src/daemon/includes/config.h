#ifndef CONFIG_H
#define CONFIG_H

typedef struct Program{
    char name[50];
    int pid;
} program_t;

static program_t programs[] = {
    {"OneNote.exe", -1}

};

#endif