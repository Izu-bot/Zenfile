#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "../includes/commands.h"

char *home_dir = NULL;

int main(int argc, char *argv[]) {
    home_dir = getenv("HOME");
    ZenConfig config;

    if (home_dir == NULL) {
        fprintf(stderr, "The variable HOME was not found in your system.\n");
        return 1;
    }

    int opt;
    char *path_conf_zen;

    static struct option long_options[] = {
        { "help",           no_argument,    0,  'h' },
        { "generate",       no_argument,    0,  'g' },
        { "configure",      no_argument,    0,  'c'}
    };

    while (1) {
        int option_index = 0;

        opt = getopt_long(argc, argv, "hgc", long_options, &option_index);

        if (opt == -1) break;

        switch (opt) {
            case 'h':
                help();
                break;
            case 'g':
                path_conf_zen = gen_conf_file(home_dir);
                printf("File created in %s\n", path_conf_zen);
                break;
            case 'c':
                configure_zenfile(home_dir, &config);
                break;
            case '?':
                fprintf(stderr, "Usage: %s <command> --help\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}