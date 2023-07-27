#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h> //Necessáro para usar as funções desta biblioteca.

//1º parâmetro é a string a ser separada, 2º parâmetro é a string que vai receber a primeira string após a remoção dos tokens.
void cpf_Separator(char src_string[], char dst_string[])
{
    char t[] = ".- \n"; //tokens a serem removidos da primeira string.
    char *portion = strtok(src_string, t);

    while (portion != NULL)
    {
        strcat(dst_string, portion);
        portion = strtok(NULL, t);
    }
    
    return;
}

int cpf_Verifier(long int cpf) //Recebe o cpf no formato long int, necessário uso da função atol para converter a string para long int.
{
    int x = 0;
    
    while (cpf != 0)
    {
        int aux = 0;
        aux = cpf % 10;
        x += aux;
        cpf -= aux;
        cpf = cpf/10;
    }
    
    int a = x % 10;
    int b = (x - a)/10;

    if (a == b) return 1; //Retorna 1 se o cpf for válido, retorna 0 se for inválido.

    return 0;
}

int digit_Verifier(char cpf[]) //Verifica se todos os elementos da string cpf são números antes de fazer conversão para long int.
{
    if (strlen(cpf) != 11) return 0; //Caso o cpf limpo tenha uma quantidade diferente do normal.

    for (int i = 0; i < strlen(cpf); i++)
    {
        if (!(isdigit(cpf[i])))
        {
            return 0; //Retorna 0 caso algum caractere não seja numérico.
        }
        
    }
    return 1; //Retorna 1 caso contrário (Não acho que precisaria explicar isso, más pelo bem da coerência aqui estamos).
}

int cpf_Autentication(char cpf[]) // Recebe a string cpf após remoção dos tokens e chama as outras funções para autenticar o cpf.
{
    if (digit_Verifier(cpf))
    {
        long int cpfnum = atol(cpf);
        if(cpf_Verifier(cpfnum))
        {
            return 1; // Retorna 1 caso o cpf seja válido.
        }
        printf("Erro! CPF inválido\n");
        return 0; // Retorna 0 caso o cpf seja inválido.
    }
    printf("Erro! CPF no formato inválido.\n");
    return 0; // Retorna -1 caso o formato do cpf seja inválido.
}