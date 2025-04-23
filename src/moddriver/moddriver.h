#ifndef MODDRIVER_H
#define MODDRIVER_H

#include <stddef.h>

typedef struct {
    const char *name;
    const char *description;
} Mod;

void launchmod(const char *modid);
const Mod *getmods(size_t *count);

#endif
