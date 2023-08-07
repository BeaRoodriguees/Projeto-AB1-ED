#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "registerUser.c"
#include "libs/searchUser.c"
#include "getDate.c"
#define MAX_LEN 100
#define LIMPAR "\e[H\e[2J"

/* FALTA:
    Ver sobre os admins
    Marcar a consulta
        Escolher por médico ou por procedimento
    As telas do Médico
*/

// Telas do Médico
void doctorScreen(int *option){
    int temp;

    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Menu do Médico\n\n");
    printf("Escolha uma das opções abaixo:\n\n");
    printf("[1] - Lista de Paciente\n[2] - Consultas do Dia\n[3] - Editar o Cadastro\n[0] - Sair\n");
    printf("Escolha: ");
    scanf("%d", &temp);

    (*option) = temp;
}

// Autentica o usuario procurando seu CPF no txt
int login(int view, int flag){
    char cpf[15];
    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Login\n\n");
    printf("Insira o seu CPF: ");
    if (flag == 0) getchar();
    fgets(cpf, 15, stdin);

    if (view == 1){
        if (searchUser(cpf, "data/listPacients.txt"))
            return 1;
    }
    else if (view == 2){
        if (searchUser(cpf, "data/listDoctors.txt"))
            return 1;
    }
    return 0;
}

int preLogin(int view){
    int flag = 0;

    while(1){
        if(!login(view, flag)){
            printf("\nFalha na autenticação. Tente novamente.\n");
            flag = 1;
            sleep(4);
            continue;
        }
        break;
    }
    flag = 0;
    printf("Autenticação realizada com sucesso! Redirecionando...\n");
    sleep(2);
    return 1;
    //prox tela
}

// Cadastra o User num .txt
int record(int view, int flag){
    char name[MAX_LEN], cpf[15], info[MAX_LEN], temp[2];
    FILE *createUser;

    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Cadastro\n\n");
    printf("Insira as informações abaixo:\n\n");
    
    printf("Nome Completo: ");
    if (flag == 0) getchar();
    fgets(name, MAX_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("CPF: ");
    fgets(cpf, 15, stdin);
    fgets(temp, 2, stdin);
    
    switch (view){
        case 1:
            printf("Doenças Importantes: ");
            fgets(info, MAX_LEN, stdin);
            info[strcspn(info, "\n")] = 0;
            createUser = fopen("data/pacient.txt", "w");
            break;
        case 2:
            printf("Opções de Procedimentos:\n\n");
            printf("[1] - Aftas\n[2] - Hipersensibilidade\n[3] - Lesões\n[4] - Pós-cirúrgia\n[5] - Nevralgia\n[6] - Consulta\n");
            getProcedure();
            
            createUser = fopen("data/doctor.txt", "w");
            break;
        case 3:
            // admin
            break;
        default:
            return 0;
            break;
    }    
    
    fprintf(createUser, "%s\n%s\n\n", name, cpf, info);
    fclose(createUser);
    return 1;
}

//Tela Inicial Geral -- Escolher o cargo
void roleScreen(int *view){
    int temp;

    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Escolha de Cargo\n\n");
    printf("Escolha uma das opções abaixo:\n\n");
    printf("[1] - Paciente\n[2] - Médico\n[3] - Admin\n");
    printf("Escolha: ");
    scanf("%d", &temp);
    
    if (temp < 1 || temp > 3){
        printf("O cargo insiro é inválido. Tente novamente.\n");
        sleep(2);
        return roleScreen(view);
    }
    (*view) = temp;
}

//Tela Incial
void homeScreen(int *choice){
    int temp;

    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Tela Inicial\n\n");
    printf("Escolha uma das opções abaixo:\n\n");
    printf("[1] - Entrar\n[2] - Cadastrar\n[0] - Sair\n");
    printf("Escolha: ");
    scanf("%d", &temp);

    if (temp < 1 || temp > 3){
        printf("A opção escolhida é inválida. Tente novamente.\n");
        sleep(2);
        return roleScreen(choice);
    }

    (*choice) = temp;
}

int main(){
    int view, choice, option = 0;

    roleScreen(&view);
    homeScreen(&choice);   

    switch (choice){
        case 0:
            return 0;
        case 1:
            preLogin(view);
            break;
        case 2:
            int flag = 0;
            while(1){    
                record(view, flag);
                if (registerUser(view) == -1){
                    printf("\nFalha no cadastro. Tente novamente.\n");
                    flag = 1;
                    sleep(4);
                    continue;
                }
                break;
            }
            flag = 0;
            printf("Cadastro realizado com sucesso! Redirecionando para tela de autenticação...\n");
            sleep(4);
            preLogin(view);
            break;
    }

    // Marcação da Consulta
    if (view == 1){
        printf(LIMPAR);
        printf("\t\tMarcação de Consulta\n\n");
        printf("Opções de Procedimentos:\n\n");
        printf("[1] - Aftas\n[2] - Hipersensibilidade\n[3] - Lesões\n[4] - Pós-cirúrgia\n[5] - Nevralgia\n[6] - Consulta\n");
        printf("Escolha um: ");
        scanf("%d", &option);

        //procurar médicos que ofertem o procedimento e mostrar na tela pro paciente escolher 

        appointment(); 
    }
    else if (view == 2){
        doctorScreen(&option);

        if (option == 1){

        }
        else if (option == 2){
            
        }
        else if (option == 3){

        }
    }

    return 0;
}