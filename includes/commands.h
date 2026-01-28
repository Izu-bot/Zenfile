#ifndef COMMANDS_H
#define COMMANDS_H

extern char* home_dir;

typedef struct {
    char images_path[526];
    char docs_path[526];
    int verbose_mode;
} ZenConfig;

void help();
char* gen_conf_file(char *home_dir);
void load_config(const char *filename, ZenConfig *config);
void configure_zenfile(char *home_dir, ZenConfig *config);

#endif