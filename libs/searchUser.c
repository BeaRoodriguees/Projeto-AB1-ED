#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

int searchUser(char *cpf, const char *fileUser){ 
    char cpf_check [15];
    char temp_name[MAX_LEN];
    char temp_infos[MAX_LEN];
    char temp[2];

    FILE *userValid = fopen(fileUser, "r");

    if (userValid == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fgets(temp_name, MAX_LEN, userValid) != NULL){
        fgets(cpf_check, 15, userValid);
        fgets(temp, 2, userValid);
        fgets(temp_infos, MAX_LEN, userValid);

        if (strcmp(cpf_check, cpf) == 0){
            printf("Acheii\n");
            fclose(userValid);
            return 1;
        }
    }
    fclose(userValid);
    return 0;
} 