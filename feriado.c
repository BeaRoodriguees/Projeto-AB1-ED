#include <stdio.h>
#include <stdlib.h>


int isBissexto(int ano)
{
    if (ano % 400 == 0)
    {
        return 1;
    }
    else if (ano % 4 == 0 && ano % 100 != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int diaDoAno(int dia, int mes, int ano)
{
    int dias = 0;
    int i;
    for (i = 1; i < mes; i++)
    {
        if (i == 2)
        {
            if (isBissexto(ano))
            {
                dias += 29;
            }
            else
            {
                dias += 28;
            }
        }
        else if (i == 4 || i == 6 || i == 9 || i == 11)
        {
            dias += 30;
        }
        else
        {
            dias += 31;
        }
    }
    dias += dia;
    return dias;
}

// Algoritmo de Meeus/Jones/Butcher para calcular a data da Páscoa
int isPascoa(int dia, int mes, int ano, int dias)
{
    int a = ano % 19;
    int b = ano / 100;
    int c = ano % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int mesPascoa = (h + l - 7 * m + 114) / 31;
    int diaPascoa = ((h + l - 7 * m + 114) % 31) + 1;
    int baseFeriado = diaDoAno(diaPascoa, mesPascoa, ano);

    if (dias == baseFeriado)
    {
        return 1;
    }
    else if (dias == baseFeriado - 1)
    {
        return 1;
    }
    else if (dias == baseFeriado - 2)
    {
        return 1;
    }
    else if (dias == baseFeriado + 60)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// algoritmo de zeller para calcular o dia da semana
int zeller(int dia, int mes, int ano)
{
    int a = (14 - mes) / 12;
    int y = ano - a;
    int m = mes + 12 * a - 2;
    int d = (dia + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    return d+1;
}

int isFeriado(int dia, int mes, int ano, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    int diaFeriado, mesFeriado;
    while (fscanf(arquivo, "%d %d", &diaFeriado, &mesFeriado) == 2)
    {
        if (dia == diaFeriado && mes == mesFeriado)
        {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

int verificaData()
{
    int dia, mes, ano, dias;
    printf("Digite o dia, mês e ano (no formato DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &ano);
    dias = diaDoAno(dia, mes, ano);

    if (isFeriado(dia, mes, ano, "data/feriados.txt"))
    {
        return 8;
    }
    else if (isPascoa(dia, mes, ano, dias))
    {
        return 8;
    }
    else
    {
        return zeller(dia, mes, ano);
    }

    return 0;
}