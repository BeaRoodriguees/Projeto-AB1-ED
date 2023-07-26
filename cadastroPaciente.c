#include <stdio.h>
#include "libs/checkName.c"
#include "libs/cpfstuff.c"
#define MAX_LEN 100

//A saída pro arquivo lisPacients.txt está sendo sobrescrita.

int main(){
    char nome[MAX_LEN];
    char doenca[MAX_LEN];
    char cpf_s[16], cpf_save[16], cpf_clean[12];

    FILE *pacientInfos = fopen("paciente.txt", "r");
    
    fgets(nome, MAX_LEN, pacientInfos);
    fgets(cpf_s, 16, pacientInfos);
    fgets(doenca, MAX_LEN, pacientInfos);

    strcpy(cpf_save, cpf_s);
    cpf_Separator(cpf_s, cpf_clean);

    if(!checkName(nome)){
        printf("Erro! Nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }

    FILE *pacientValid = fopen("listPacients.txt", "w");

    fprintf(pacientValid, "%s%s%s\n", nome, cpf_save, doenca);
    fclose(pacientValid);
    fclose(pacientInfos);
    return 0;
}
