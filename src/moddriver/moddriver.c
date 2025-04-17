#include <stdio.h>

void launchmod(const char* modid) { // TODO: mod implementation
    printf("lol: %s", modid);
}

typedef struct {
    const char* name;
    const char* description;
} Mod;

const Mod* getmods(size_t* count) { // TODO: get modlist
    static const Mod modlist[] = {
        {"mod1", "hi chat"},
        {"mod2", "guh"},
    };
    *count = sizeof(modlist) / sizeof(modlist[0]);
    return modlist;
}