#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void string_Separator(char src_string[], char dst_string[])
{
    char t[] = ".-";
    char *portion = strtok(src_string, t);

    while (portion != NULL)
    {
        strcat(dst_string, portion);
        portion = strtok(NULL, t);
    }
    
    return;
}

int cpf_Verifier(long int cpf) {
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

    if (a == b) return 1;

    return 0;
}