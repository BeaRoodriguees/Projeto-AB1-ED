#include <stdio.h>
#include <string.h>
#include "libs/checkName.c"
#include "libs/checkCPF.c"
#define MAX_LEN 100

void getInfos(){
    FILE *doctorInfos = fopen("data/listDoctors.txt", "ab");
    char *infos, *t;
    printf("Informe: ");
    fgets(infos, 50, stdin);

    t = strtok(infos,", ");

    while (t != NULL)
    {
        if (atoi(t) > 0 && atoi(t) < 7) fprintf(doctorInfos, "%d ", atoi(t));
        t = strtok(NULL, ", ");
    }
    printf("\n");
    fclose(doctorInfos);
}

//obtem os dados gerados pelo formulario
int getUser(char *name, char *cpf, char *infos, const char *fileUser){
    FILE *userInfos = fopen(fileUser, "r");
    char temp[2];
    
    if (userInfos == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fgets(name, MAX_LEN, userInfos);
    name[strcspn(name, "\n")] = 0;
    fgets(cpf, 15, userInfos);
    fgets(temp, 2, userInfos);
    fgets(infos, MAX_LEN, userInfos);
    infos[strcspn(infos, "\n")] = 0;

    fclose(userInfos);
    return 1;
}

// funcao que ler o arquivo carrega as strings e faz uma busca "linear" verificando se o cpf consta no .txt
int validReg(char *cpf, const char *fileUser){ 
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
            printf("%s ", cpf);
            printf("é CPF já utilizado.\n");
            fclose(userValid);
            return 0;
        }
    }
    fclose(userValid);
    return 1;
} 

//funçao que salva o cadastro
int salveReg(char *name, char *cpf_save, char *infos, const char *userFile){
    FILE *userValid = fopen(userFile, "ab");

    if (userValid == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fprintf(userValid, "%s\n%s\n%s\n", name, cpf_save, infos);
    fclose(userValid);
}

int registerUser(int view){
    char name[MAX_LEN];
    char infos[MAX_LEN];
    char cpf[15], cpf_save[15], cpf_clean[11];

    if (view == 1)
        getUser(name, cpf, infos, "data/pacient.txt");
    else if (view == 2)
        getUser(name, cpf, infos, "data/doctor.txt");

    strcpy(cpf_save, cpf);
    cpf_Separator(cpf, cpf_clean);

    if(!checkName(name)){
        printf("Erro! Nome inválido.\n");
        return -1;
    }
   
    if(!cpf_Autentication(cpf_clean)){
        return -1;
    }

    if (view == 1){
        if(validReg(cpf_save, "data/listPacients.txt")){
            salveReg(name, cpf_save, infos, "data/listPacients.txt");
            return 1;   
        }
    }
    else if (view == 2){
        if(validReg(cpf_save, "data/listDoctors.txt")){
            salveReg(name, cpf_save, infos, "data/listDoctors.txt");
            
            printf("\nOpções de Procedimentos:\n");
            printf("[1] - Aftas\n[2] - Hipersensibilidade\n[3] - Lesões\n[4] - Pós-cirúrgia\n[5] - Nevralgia\n[6] - Consulta\n");
            getInfos();

            printf("Informe os dias de atendimento (2 - Seg, ..., 7 - Sab): ");
            getInfos();
            return 1;    
        }
    }
    
    return -1;
}