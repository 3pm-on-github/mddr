#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "moddriver/moddriver.h"

const char* VERSION = "v0.0.01B";

char* get_input() {
    static char buffer[128];

    printf(">>> ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        return buffer;
    }

    return "";
}


void clearcmd() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void rainbow(const char* text, unsigned int secs) {
    const char* colors[] = {
        "\033[31m",
        "\033[33m",
        "\033[32m",
        "\033[34m",
        "\033[35m"
    };
    const char* reset = "\033[0m";

    for (unsigned int s = 0; s < secs; s++) {
        for (int i = 0; i < 5; i++) {
            printf("\r%s%s%s", colors[i], text, reset);
            fflush(stdout);
            usleep(200000);
        }
    }

    printf("\n");
}

int run() {
    clearcmd();
    printf("\rMDDR %s by 3pm\n\n", VERSION);
    printf("NOTE: to run mods, you need to run mddr as administrator.\n");
    printf("1. Exit\n");
    printf("2. Run a mod\n");
    printf("3. Mod list\n");
    printf("4. About\n");
    char* option = get_input();
    if (strcmp(option, "1") == 0) {
        clearcmd();
        exit(0);
    } else if (strcmp(option, "2") == 0) {
        clearcmd();
        printf("What's the mod id?\n");
        char* modid = get_input();
        clearcmd();
        launchmod(modid);
        run();
    } else if (strcmp(option, "3") == 0) {
        clearcmd();
        printf("Mods:\n");
        size_t mod_count;
        const Mod* modlist = getmods(&mod_count);
        for (size_t i = 0; i < mod_count; ++i) {
            printf("%s: %s\n", modlist[i].name, modlist[i].description);
        }
        printf("Press enter to go back to the menu\n");
        char temp[4];
        fgets(temp, sizeof(temp), stdin);
        run();
    } else if (strcmp(option, "4") == 0) {
        printf("MDDR %s\n", VERSION);
        printf("© 2024 - 2025\n");
        printf("Credits:\n");
        printf("Creator: 3pm\n");
        printf("\nnote from 3pm: do not use this tool while drunk\n\n");
        printf("█████████████████\n");
        printf("██             ██\n");
        printf("██   ██   ██   ██\n");
        printf("██             ██\n");
        printf("██  █████████  ██\n");
        printf("██             ██\n");
        printf("█████████████████\n");
        printf("                  \033[34m[mddr]\033[0m\n\n");
        printf("Press enter to go back to the menu\n");
        char temp[4];
        fgets(temp, sizeof(temp), stdin);
        run();
    } else {
        printf("Error: Invalid option\n");
        printf("Press any key to go back to the menu\n");
        char temp[4];
        fgets(temp, sizeof(temp), stdin);
        run();
    }
    free(option);
}

int main() {
    clearcmd();
    rainbow("Welcome to MDDR!", 2);
    run();
}