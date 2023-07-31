#include <stdio.h>
#include "libs/checkName.c"
#include "libs/checkCPF.c"
#include "libs/searchUser.c"
#define MAX_LEN 100

//falta implentar se o usuário já existe
//Algoritmo cadastra apenas 1 médico

int main(){
    char name[MAX_LEN];
    char cpf[15], cpf_save[15], cpf_clean[12], temp[2];
    char specialties[MAX_LEN];
    int serviceDays[6], i = 0;

    FILE *doctorInfos = fopen("data/doctor.txt", "r"); //abre o arquivo doctor.txt onde tem as informações do médico

    //bloco de leitura das entradas
    fgets(name, MAX_LEN, doctorInfos);
    name[strcspn(name, "\n")] = 0;
    fgets(cpf, 15, doctorInfos);
    fgets(temp, 2, doctorInfos);
    fgets(specialties, MAX_LEN, doctorInfos);
    specialties[strcspn(specialties, "\n")] = 0;

    while(fscanf(doctorInfos, "%d", &serviceDays[i]) != EOF ){
       i++;
    }
    printf("%d\n", i);
    

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
    if (searchUser()){ //Confere se o médico já possui cadastro
        printf("O médico já possui cadastro.\n");
        return -1;
    }

    //Gravação das entradas em um arquivo de texto listdoctors.txt
    FILE *doctorValid = fopen("data/listDoctors.txt", "ab");
    fprintf(doctorValid, "%s %s %s ", name, cpf_save, specialties);

   for(int j = 0; j < i; j++)
        fprintf(doctorValid, "%d ", serviceDays[j]);
    fprintf(doctorValid, "\n");
    
    
    fclose(doctorValid);
    fclose(doctorInfos);
    return 0;
}