#include <stdio.h>
#include "libs/checkName.c"
#include "libs/checkCPF.c"
#define MAX_LEN 100

/* 
Não está pegando as doenças
*/


//obtem os dados gerados pelo formulario
int getPacient(char *name, char *cpf, char *doenca){
    FILE *pacientInfos = fopen("data/pacient.txt", "r");
    char temp[2];
    
    if (pacientInfos == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fgets(name, MAX_LEN, pacientInfos);
    name[strcspn(name, "\n")] = 0;
    fgets(cpf, 15, pacientInfos);
    fgets(temp, 2, pacientInfos);
    fgets(doenca, MAX_LEN, pacientInfos);
    doenca[strcspn(doenca, "\n")] = 0;

    fclose(pacientInfos);
    return 1;
}

// funcao que ler o arquivo carrega as strings e faz uma busca "linear" verificando se o cpf consta no .txt
int validaCad(char *cpf){ 
    char cpf_check [15];
    char temp_name[MAX_LEN];
    char temp_doenca[MAX_LEN];
    char temp[2];

    FILE *pacientValid = fopen("data/listPacients.txt", "r");

    if (pacientValid == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fgets(temp_name, MAX_LEN, pacientValid) != NULL){
        fgets(cpf_check, 15, pacientValid);
        fgets(temp, 2, pacientValid);
        fgets(temp_doenca, MAX_LEN, pacientValid);

        if (strcmp(cpf_check, cpf) == 0){
            printf("%s ", cpf);
            printf("é CPF já utilizado.\n");
            fclose(pacientValid);
            return 0;
        }
    }

    fclose(pacientValid);
    return 1;
} 

//funçao que salva o cadastro
int salvaCad(char *name, char *cpf_save, char *doenca){
    FILE *pacientValid = fopen("data/listPacients.txt", "ab");

    if (pacientValid == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fprintf(pacientValid, "%s\n%s\n%s\n", name, cpf_save, doenca);
    fclose(pacientValid);
}

int main(){
    char name[MAX_LEN];
    char doenca[MAX_LEN];
    char cpf[15], cpf_save[15], cpf_clean[11];

    getPacient(name, cpf, doenca);

    strcpy(cpf_save, cpf);
    cpf_Separator(cpf, cpf_clean);

    if(!checkName(name)){
        printf("Erro! Nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }

    if(validaCad(cpf_save)){
        salvaCad(name, cpf_save, doenca);
    }

    return 1;
}