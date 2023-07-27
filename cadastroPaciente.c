#include <stdio.h>
#include "libs/checkName.c"
#include "libs/cpfstuff.c"
#define MAX_LEN 100

//falta implentar se o usuário já existe

int main(){
    char nome[MAX_LEN];
    char doenca[MAX_LEN];
    char cpf_s[15], cpf_save[15], cpf_clean[12];
    char temp[2];

    FILE *pacientInfos = fopen("paciente.txt", "r");
    
    fgets(nome, MAX_LEN, pacientInfos);
    nome[strcspn(nome, "\n")] = 0;
    fgets(cpf_s, 15, pacientInfos);
    fgets(temp, 2, pacientInfos);
    fgets(doenca, MAX_LEN, pacientInfos);
    doenca[strcspn(doenca, "\n")] = 0;

    strcpy(cpf_save, cpf_s);
    cpf_Separator(cpf_s, cpf_clean);

    if(!checkName(nome)){
        printf("Erro! Nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }

    FILE *pacientValid = fopen("listPacients.txt", "ab");

    fprintf(pacientValid, "%s %s %s\n", nome, cpf_save, doenca);
    fclose(pacientValid);
    fclose(pacientInfos);
    return 0;
}
