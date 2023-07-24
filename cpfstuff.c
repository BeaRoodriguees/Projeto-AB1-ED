#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void string_Separator(char src_string[], char dst_string[])//1º parâmetro é a string a ser separada, 2º parâmetro é a string que vai receber a primeira string após a remoção dos tokens.
{
    char t[] = ".-"; //tokens a serem removidos da primeira string.
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