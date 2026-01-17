#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../includes/commands.h"

void help() {
    printf("Usage: zenfile [options]\n\n\n");
    printf("Organize your directory by moving files to protected directories.\n\n\n");
    printf("COMMANDS\n\n");
    printf("-c, --configure         create the configuration file.");
    printf("-h, --help              help for using zenfile.");
    printf("OPTIONS\n\n");
    printf("EXAMPLES\n\n");
    printf("Use: 'zenfile <command> --help' for more information about the command.\n");
}

/// @brief Gera o arquivo de configuração da ferramenta.
/// @return Retorna o caminho completo aonde foi gerado.
char* gen_conf_file(char *home_dir) {
    if (home_dir == NULL) return NULL;

    static char path[512];

    snprintf(path, sizeof(path), "%s/.config/zenfile", home_dir);

    mkdir(path, 0700);

    static char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/zenfile.conf", path);

    if (access(full_path, F_OK) == 0) {
        return full_path;
    } else {
        FILE *file = fopen(full_path, "w");
        fclose(file);
    }

    return full_path;
}

/// @brief Essa função lê o caminho do diretorio para configurar o zenfile
/// após ler o caminho ele abre o arquivo zenfile.conf e busca as variaveis
/// necessárias para sua configuraçao.
/// @param filename Caminho completo do arquivo que deve ser aberto.
void configure_zenfile(char *filename) {
    
}