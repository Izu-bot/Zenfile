#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "../includes/commands.h"

char *home_dir = NULL;

int main(int argc, char *argv[]) {
    home_dir = getenv("HOME");

    if (home_dir == NULL) {
        fprintf(stderr, "The variable HOME was not found in your system.\n");
        return 1;
    }

    ZenConfig config;

    char *default_conf_path = gen_conf_file(home_dir);
    load_config(default_conf_path, &config);


    int opt;
    static struct option long_options[] = {
        { "help",           no_argument,        0,  'h' },
        { "generate",       no_argument,        0,  'g' },
        { "configure",      no_argument,        0,  'c' },
        { "move",           required_argument,  0,  'm' },
        { 0, 0, 0, 0},
    };

    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "hgcm:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                help();
                break;
            case 'g':
                printf("Configuration file is at: %s\n", default_conf_path);
                break;
            case 'c':
                configure_zenfile(home_dir, &config);
                break;
            case 'm':
                organize_directory(optarg, &config);
                break;
            case '?':
                help();
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}
