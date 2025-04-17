#ifndef MODDRIVER_H
#define MODDRIVER_H

typedef struct {
    const char* name;
    const char* description;
} Mod;

void launchmod();
const Mod* getmods();

#endif