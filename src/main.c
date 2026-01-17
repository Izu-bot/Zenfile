#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/commands.h"

int main(int argc, char *argv[]) {
    int opt;
    char *path_conf_zen;

    while ((opt = getopt(argc, argv, "hc")) != -1) {
        switch (opt) {
            case 'h':
                help();
                break;
            case 'c':
                path_conf_zen = gen_conf_file();
                printf("File created in %s\n", path_conf_zen);
                break;
            case '?':
                fprintf(stderr, "Usage: %s <command> --help\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}