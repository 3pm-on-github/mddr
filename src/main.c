#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

const char* VERSION = "v0.0.01B";

char* get_input() {
    size_t buffer_size = 2;
    char* input = (char*)malloc(buffer_size * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    printf(">>> ");
    fgets(input, buffer_size, stdin);

    input[strcspn(input, "\n")] = '\0';

    return input;
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


int main() {
    clearcmd();
    rainbow("Welcome to MDDR!", 2);
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
    } else if (strcmp(option, "4") == 0) {
        printf("MDDR %s\n", VERSION);
        printf("© 2024 - 2024\n");
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
        char* unused = get_input(); // BUG: it just skips it
        main();
    } else {
        printf("Error: Invalid option\n");
        printf("Press any key to go back to the menu\n");
        char* unused = get_input(); // BUG: doesnt clear the cmd
        main();
    }
    free(option);
}