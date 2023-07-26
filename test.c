#include <stdio.h>
#include "libs/checkName.c"
#include "libs/cpfstuff.c"
#define MAX_LEN 100

int main(){
    char nome[MAX_LEN];
    char cpf_s[16];
    char doenca[MAX_LEN];

    FILE *pacientInfos = fopen("paciente.txt", "r");
    
    fgets(nome, MAX_LEN, pacientInfos);
    fgets(cpf_s, 16, pacientInfos);
    fgets(doenca, MAX_LEN, pacientInfos);
    
    printf("%s%s%s\n", nome, cpf_s, doenca);

    if(!checkName(nome)){
        printf("Erro! Nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_s)){
        printf("Erro! CPF inválido.\n");
        return -1;
    }
    
    fclose(pacientInfos);

    fopen()
    fprintf()


    fclose(pacientInfos);
    return 0;
}
