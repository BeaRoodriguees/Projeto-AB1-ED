#include <stdio.h>
#include "libs/checkName.c"
#include "libs/checkCPF.c"
#define MAX_LEN 100

/*
Não está lendo dps do CPF pra Bia
Falta implementar a leitura dos dias de atendimento
*/

// Obtem os dados gerados pelo formulario
int getDoctor(char *name, char *cpf, char *specialties, int *serviceDays){
    FILE *doctorInfos = fopen("data/doctor.txt", "r"); //abre o arquivo doctor.txt onde tem as informações do médico
    char temp[2];
    
    if (doctorInfos == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fgets(name, MAX_LEN, doctorInfos);
    name[strcspn(name, "\n")] = 0;
    fgets(cpf, 15, doctorInfos);
    fgets(temp, 2, doctorInfos);
    fgets(specialties, MAX_LEN, doctorInfos);
    specialties[strcspn(specialties, "\n")] = 0;

    fclose(doctorInfos);
    return 1;
}

// funcao que ler o arquivo carrega as strings e faz uma busca "linear" verificando se o cpf consta no .txt
int validCad(char *cpf){ 
    char cpf_check [15];
    char temp_name[MAX_LEN];
    char temp_specialties[MAX_LEN];
    char temp[2];

   FILE *doctorValid = fopen("data/listDoctors.txt", "r");

    if (doctorValid == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fgets(temp_name, MAX_LEN, doctorValid) != NULL){
        fgets(cpf_check, 15, doctorValid);
        fgets(temp, 2, doctorValid);
        fgets(temp_specialties, MAX_LEN, doctorValid);

        if (strcmp(cpf_check, cpf) == 0){
            printf("%s ", cpf);
            printf("é CPF já utilizado.\n");
            fclose(doctorValid);
            return 0;
        }
    }
    
    fclose(doctorValid);
    return 1;
}

int salveCad(char *name, char *cpf_save, char *specialties, int *serviceDays){
    FILE *pacientValid = fopen("data/listDoctors.txt", "ab");

    if (pacientValid == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fprintf(pacientValid, "%s\n%s\n%s\n\n", name, cpf_save, specialties);
    fclose(pacientValid);
}

int registerDoctor(){
    char name[MAX_LEN];
    char cpf[15], cpf_save[15], cpf_clean[12], temp[2];
    char specialties[MAX_LEN];
    int serviceDays[6];

    getDoctor(name, cpf, specialties, serviceDays);

    strcpy(cpf_save, cpf); //salvar o cpf em um backup
    cpf_Separator(cpf, cpf_clean); //limpar o cpf

    //Checagem da validade das entradas
    if(!checkName(name)){
        printf("Erro! nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }

    if(validCad(cpf_save)){
        salveCad(name, cpf_save, specialties, serviceDays);
    }

    return 1;
}