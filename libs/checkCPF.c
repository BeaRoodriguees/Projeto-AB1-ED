#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> //Necessáro para usar as funções desta biblioteca.

//1º parâmetro é a string a ser separada, 2º parâmetro é a string que vai receber a primeira string após a remoção dos tokens.
void cpf_Separator(char src_string[], char dst_string[])
{
    memset(dst_string,0,strlen(dst_string)); //limpar a string pra o proximo uso
    char t[] = ".- \n"; //tokens a serem removidos da primeira string.
    char *portion = strtok(src_string, t);

    while (portion != NULL)
    {
        strcat(dst_string, portion);
        portion = strtok(NULL, t);
    }
    
    return;
}

void num_Separator(int *array, int tam, long int num) //Recebe um array, seu tamano e um número long int para ser transformado em array, onde cada posição do array corresponde a um único dígito do número.
{
    for (int i = tam - 1; i > -1; i--)
    {
        int aux;
        aux = (num % 10);
        array[i] = aux;
        num = (num - aux)/10;
    }
    
    return;
}

int cpf_Verifier(long int cpf) //Recebe o Cpf no formato long int e retorna 1 caso válido e 0 caso inválido.
{
    int *ptr = (int*) calloc(11, sizeof(int)), total = 0, digit = 0;

    if (ptr == NULL)
    {
        printf("Erro na alocação.");
        return 0;
    }

    num_Separator(ptr, 11, cpf);
    
    for (int i = 0, mult = 10; i < 9; i++, mult--)
    {
        total += (ptr[i] * mult);
    }
    if ((total % 11) >= 2)
    {
        digit = 11 - (total % 11);
    }
    else
    {
        digit = 0;
    }
    
    if (digit == ptr[9])
    {
        total = 0;
        for (int i = 0, mult = 11; i < 10; i++, mult--)
        {
            total += (ptr[i] * mult);
        }
        if ((total % 11) >= 2)
        {
            digit = 11 - (total % 11);
        }
        else
        {
            digit = 0;
        }
        if (digit == ptr[10])
        {
            free(ptr);
            return 1;
        }
        free(ptr);
        return 0;
    }
    free(ptr);
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
    return 0; // Retorna 0 caso o formato do cpf seja inválido.
}