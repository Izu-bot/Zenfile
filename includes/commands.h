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
int move_file_to_dir(char *source_file, char *dest_folder);
int has_extension(char *filename, char *ext);
void organize_directory(char *target_dir, ZenConfig *config);

#endif