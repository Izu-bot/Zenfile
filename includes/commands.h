#ifndef COMMANDS_H
#define COMMANDS_H

extern char* home_dir;

void help();
char* gen_conf_file(char *home_dir);
void configure_zenfile(char *filename);

#endif