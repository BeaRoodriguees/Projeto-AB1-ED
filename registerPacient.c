#include <stdio.h>
#include "libs/checkName.c"
#include "libs/checkCPF.c"
#include "libs/searchUser.c"
#define MAX_LEN 100

//falta implentar se o usuário já existe
//Algoritmo cadastra apenas 1 paciente

int main(){
    char name[MAX_LEN];
    char disease[MAX_LEN];
    char cpf_s[15], cpf_save[15], cpf_clean[12];
    char temp[2];

    FILE *patientInfos = fopen("data/patient.txt", "r"); //abre o arquivo patient.txt onde tem as informações do paciente
    
    //bloco de leitura das entradas
    fgets(name, MAX_LEN, patientInfos);
    name[strcspn(name, "\n")] = 0;
    fgets(cpf_s, 15, patientInfos);
    fgets(temp, 2, patientInfos);
    fgets(disease, MAX_LEN, patientInfos);
    disease[strcspn(disease, "\n")] = 0;

    strcpy(cpf_save, cpf_s); //salvar o cpf em um backup
    cpf_Separator(cpf_s, cpf_clean); //limpar o cpf


    //Checagem da validade das entradas
    if(!checkName(name)){
        printf("Erro! nome inválido.\n");
        return -1;
    }
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }
    if (searchUser()){ //ver se o paciente já possui cadastro
        printf("O paciente já possui cadastro.\n");
        return -1;
    }

    //Gravação das entradas em um arquivo de texto lispatients
    FILE *patientValid = fopen("data/listpatients.txt", "ab");
    fprintf(patientValid, "%s %s %s\n", name, cpf_save, disease);
    
    fclose(patientValid);
    fclose(patientInfos);
    return 0;
}
