#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    const char *description;
} Mod;

static int read_mddri_file(const char *path, char **name_out, char **desc_out) { //TODO: mod implementation v2.0 btw idk if this works
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    size_t len = 0;
    char *line = NULL;
    ssize_t nread;

    char *modname = NULL;
    char *moddesc = NULL;

    if ((nread = getline(&line, &len, f)) != -1) {
        if (strncmp(line, "modname: ", 9) == 0)
            modname = strdup(line + 9);
    }
    if ((nread = getline(&line, &len, f)) != -1) {
        if (strncmp(line, "moddescription: ", 16) == 0)
            moddesc = strdup(line + 16);
    }

    free(line);
    fclose(f);

    if (!modname || !moddesc) {
        free(modname);
        free(moddesc);
        return 0;
    }

    modname[strcspn(modname, "\r\n")] = 0;
    moddesc[strcspn(moddesc, "\r\n")] = 0;

    *name_out = modname;
    *desc_out = moddesc;
    return 1;
}

void launchmod(const char *modid) {
    DIR *dir = opendir("/mddr/mods");
    if (!dir) {
        printf("Error reading directory\n");
        return;
    }

    struct dirent *entry;
    int found = 0;

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            char info_path[512];
            snprintf(info_path, sizeof(info_path), "/mddr/mods/%s/info.mddri", entry->d_name);

            char *name = NULL, *desc = NULL;
            if (read_mddri_file(info_path, &name, &desc)) {
                if (strcmp(name, modid) == 0)
                    found = 1;
                free(name);
                free(desc);
            }
        }
    }
    closedir(dir);

    if (!found)
        printf("Error: Mod Not Found\n");
}

static Mod *modlist_cache = NULL;
static size_t modlist_count = 0;

const Mod *getmods(size_t *count) { //BUG: where are my mods (mods arent being showed in the modlist)
    if (modlist_cache) {
        *count = modlist_count;
        return modlist_cache;
    }

    DIR *dir = opendir("/mddr/mods");
    if (!dir) {
        *count = 0;
        return NULL;
    }

    struct dirent *entry;
    size_t cap = 8;
    Mod *mods = malloc(cap * sizeof(Mod));

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            char info_path[512];
            snprintf(info_path, sizeof(info_path), "/mddr/mods/%s/info.mddri", entry->d_name);

            char *name = NULL, *desc = NULL;
            if (read_mddri_file(info_path, &name, &desc)) {
                if (modlist_count == cap) {
                    cap *= 2;
                    mods = realloc(mods, cap * sizeof(Mod));
                }
                mods[modlist_count].name = name;
                mods[modlist_count].description = desc;
                modlist_count++;
            }
        }
    }
    closedir(dir);

    modlist_cache = mods;
    *count = modlist_count;
    return modlist_cache;
}
