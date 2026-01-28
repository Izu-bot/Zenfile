#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "../includes/commands.h"

/// @brief Método de ajuda/manual ao usuário de como usar o utilitário
void help() {
    printf("Usage: zenfile [options]\n\n\n");
    printf("Organize your directory by moving files to protected directories.\n\n\n");
    printf("COMMANDS\n\n");
    printf("-g, --generate          generate the configuration file.");
    printf("-c, --configure         create the configuration file.");
    printf("-h, --help              help for using zenfile.");
    printf("OPTIONS\n\n");
    printf("EXAMPLES\n\n");
    printf("Use: 'zenfile <command> --help' for more information about the command.\n");
}

/// @brief Gera o arquivo de configuração da ferramenta
/// @param home_dir Diretório padrão do usuário
/// @return Retorna o caminho completo aonde foi gerado
char* gen_conf_file(char *home_dir) {
    if (home_dir == NULL) return NULL;

    static char path[512];

    snprintf(path, sizeof(path), "%s/.config/zenfile", home_dir);

    mkdir(path, 0700);

    static char full_path[526];
    snprintf(full_path, sizeof(full_path), "%s/zenfile.conf", path);

    if (access(full_path, F_OK) == 0) {
        return full_path;
    } else {
        FILE *file = fopen(full_path, "w");
        if (file) {
            fprintf(file, "# Zenfile configuration file\n");
            fprintf(file, "# Define the absolute paths below\n\n");
            fprintf(file, "images=%s/Images\n", home_dir);
            fprintf(file, "docs=%s/Documents\n", home_dir);
            fclose(file);
        }
    }

    return full_path;
}

/// @brief Carrega o arquivo de configuraçao do Zenfile
/// @param filename Nome do arquivo de cofniguraçao
/// @param config Struct para configurar o Zenfile
void load_config(const char *filename, ZenConfig *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("The configuration file could not be opened");
        return;
    }

    char line[512];

    strcpy(config->images_path, "/tmp");
    strcpy(config->docs_path, "/tmp");
    
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "images=", 7) == 0) {
            strcpy(config->images_path, line + 7);
        } else if (strncmp(line, "docs=", 5) == 0) {
            strcpy(config->docs_path, line + 5);
        }
    }

    fclose(file);
}

/// @brief Essa função lê o caminho do diretorio para configurar o zenfile
/// após ler o caminho ele abre o arquivo zenfile.conf e busca as variaveis
/// necessárias para sua configuraçao
/// @param home_dir Diretório padrão do usuário
/// @param config Struct para configuração do Zenfile
void configure_zenfile(char *home_dir, ZenConfig *config) {
    char *conf_path = NULL;
    char custom_path[256];
    char response;

    printf("Is Zenfile in the default path? (y/n): ");
    scanf(" %c", &response);

    if (response == 'y' || response == 'Y') {
        conf_path = gen_conf_file(home_dir);
    } else {
        printf("Enter the custom configuration path: ");
        scanf("%s", custom_path);
        conf_path = custom_path;
    }

    load_config(conf_path, config);

    printf("Loaded configuration!\n");
}