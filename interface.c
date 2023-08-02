#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "registerPacient.c"

#define MAX_LEN 100
#define LIMPAR "\e[H\e[2J"

int login(){
    char cpf[15];
    printf(LIMPAR);
    printf("\t\tMarcação de Consulta -- Login\n\n");
    printf("Insira o seu CPF: ");
    fgets(cpf, 15, stdin);

    /* procurá-lo na lista || autenticar
    se autenticado:
        Madar para tela de consultas
    se não:
        Tente outra veeez!
    */
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
        printf("Valor do Cargo insiro é inválido.");
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
            login();
            break;

        case 2:
            while(1){
                record(view, c);
                int reg = registerPacient();
                printf("%d", reg);
                if(reg == -1){
                    printf("\nCadastro inválido. Tente novamente.\n");
                    c++;
                    sleep(4);
                    continue;
                }
                break;
            }
            
            printf("\nCadastro realizado com sucesso! Redirecionando para tela de login...\n");
            sleep(4);
            login();
            break;
        
        default:
            printf("Escolha inválida. Por favor, tente novamente.\n");
            // Chamar o Tela Inicial
            break;
    }
}