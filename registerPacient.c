#include <stdio.h>
#include "libs/checkName.c"
#include "libs/checkCPF.c"
#define MAX_LEN 100

//obtem os dados gerados pelo formulario
int getPacient(char *nome, char *cpf_s, char *doenca){
    FILE *pacientInfos = fopen("data/pacient.txt", "r");
    char temp[2];
    
    if (pacientInfos == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    fgets(nome, MAX_LEN, pacientInfos);
    nome[strcspn(nome, "\n")] = 0;
    fgets(cpf_s, 15, pacientInfos);
    fgets(temp, 2, pacientInfos);
    fgets(doenca, MAX_LEN, pacientInfos);
    doenca[strcspn(doenca, "\n")] = 0;
    
    fclose(pacientInfos);
    return 1;

}

// funcao que ler o arquivo carrega as strings e faz uma busca "linear" verificando se o cpf consta no .txt
int validaCad(char *cpf_s){ 
    char cpf_check [15];
    char temp_name[MAX_LEN];
    char temp_doenca[MAX_LEN];
    char temp[2];

    FILE *pacientValid = fopen("data/listPacients.txt", "r");
    

    if (pacientValid == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    while (fgets(temp_name, MAX_LEN, pacientValid)!=NULL){
        fgets(cpf_check, 15, pacientValid);
        fgets(temp, 2, pacientValid);
        fgets(temp_doenca, MAX_LEN, pacientValid);

        if (strcmp(cpf_check, cpf_s)){
            printf("%s  ", cpf_s);
            printf("CPF já utilizado.\n");
            fclose(pacientValid);
            return 0;
        }
    }

    fclose(pacientValid);
    return 1;
} 

//funçao que salva o cadastro
int salvaCad(char *nome, char *cpf_save, char *doenca ){
    char cpf_check [15];
    char temp_name[MAX_LEN];
    char temp_doenca[MAX_LEN];

    FILE *pacientValid = fopen("listPacients.txt", "ab");

    if (pacientValid == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    while (fscanf(pacientValid, "%s %s %s", temp_name, cpf_check, temp_doenca) != EOF){   
        printf("%s",cpf_check);
        
        if (cpf_check == cpf_save){   
            printf("CPF já utilizado");
            fclose(pacientValid);
            return 0;
        }
    }

    fprintf(pacientValid, "%s\n%s\n%s\n", nome, cpf_save, doenca);
    fclose(pacientValid);
}

int main(){
    char nome[MAX_LEN], temp_nome[MAX_LEN];
    char doenca[MAX_LEN],temp_doenca[MAX_LEN];
    char cpf_s[15], cpf_save[15], cpf_clean[11];

    getPacient(nome, cpf_s,doenca);

    strcpy(cpf_save, cpf_s);
    cpf_Separator(cpf_s, cpf_clean);

    if(!checkName(nome)){
        printf("Erro! Nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }

    if(validaCad(cpf_save)){
        salvaCad(nome, cpf_save, doenca);
    }

    return 0;
}