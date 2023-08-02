#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "registerUser.c"
#include "libs/searchUser.c"
#define MAX_LEN 100
#define LIMPAR "\e[H\e[2J"

/*
    Ver sobre os admins
    Marcar a consulta
    As telas do Médico
*/


// Autentica o usuario procurando seu CPF no txt
int login(int view, int c){
    char cpf[15];
    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Login\n\n");
    printf("Insira o seu CPF: ");
    if (c == 0) getchar();
    fgets(cpf, 15, stdin);

    if (view == 1){
        if (searchUser(cpf, "data/listPacients.txt")){
            // Marcar a consulta
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (view == 2){
        if (searchUser(cpf, "data/listDoctors.txt")){
            // Prox tela
            return 1;
        }
        else{
            return 0;
        }
    }

}


// Cadastra o User num .txt
int record(int view, int c){
    char name[MAX_LEN], cpf[15], info[MAX_LEN], temp[2];
    FILE *createUser;

    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Cadastro\n\n");
    printf("Insira as informações abaixo:\n\n");
    
    printf("Nome Completo: ");
    if (c == 0) getchar();
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
            printf("Especialidade / Procedimentos: ");
            fgets(info, MAX_LEN, stdin);
            info[strcspn(info, "\n")] = 0;
            createUser = fopen("data/doctor.txt", "w");
            break;
        case 3:
            // admin
            break;
        default:
            return 0;
            break;
    }    
    
    fprintf(createUser, "%s\n%s\n%s\n\n", name, cpf, info);
    fclose(createUser);
    return 1;
}

int main(){
    int view, choice, c = 0;

    //Tela Inicial Geral -- Escolher o cargo
    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Escolha de Cargo\n\n");
    printf("Escolha uma das opções abaixo:\n\n");
    printf("[1] - Paciente\n[2] - Médico\n[3] - Admin\n");
    printf("Escolha: ");
    scanf("%d", &view);
    
    if (view < 1 || view > 3){
        printf("O cargo insiro é inválido.");
        sleep(4);
        //chamar o Tela Inicial Geral
    }

   //Tela Incial
    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Tela Inicial\n\n");
    printf("Escolha uma das opções abaixo:\n\n");
    printf("[1] - Entrar\n[2] - Cadastrar\n[0] - Sair\n");
    printf("Escolha: ");
    scanf("%d", &choice);

    switch (choice){
        case 0:
            return 0;

        case 1: // ajeitar
            while(1){    
                if(!login(view, c)){
                    printf("\nFalha no cadastro. Tente novamente.\n");
                    c = 1;
                    sleep(4);
                    continue;
                }
                break;
            }
            c = 0;
            printf("Cadastro realizado com sucesso! Redirecionando para tela de autenticação...\n");
            sleep(4);
            //marcarConsulta
            break;


        case 2:
            while(1){    
                record(view, c);
                if (registerUser(view) == -1){
                    printf("\nFalha no cadastro. Tente novamente.\n");
                    c = 1;
                    sleep(4);
                    continue;
                }
                break;
            }
            c = 0;
            printf("Cadastro realizado com sucesso! Redirecionando para tela de autenticação...\n");
            sleep(4);
            //chamar login -- Cuidar do loop de erro
            break;

        default:
            printf("Escolha inválida. Por favor, tente novamente.\n");
            // Chamar o Tela Inicial
            break;
    }
}