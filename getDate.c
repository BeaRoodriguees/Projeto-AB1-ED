#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "libs/feriado.c"

typedef struct tm data;

int anoBi (int ano){
    if (ano % 100 == 0 && ano % 400 != 0)
        return 0;
    else if (ano % 4 == 0 || ano % 400 == 0)
        return 1;
    else
        return 0;
}

void sepData (char *c, data *consulta){
    int i = 0;
    char *t;
  
    t = strtok(c, "/-.");
  
    while (t != NULL) {
        if (i == 0)
            consulta->tm_mday = atoi(t);
        else if (i == 1)
            consulta->tm_mon = atoi(t);
        else if (i == 2)
            consulta->tm_year = atoi(t);

        t = strtok(NULL, "/ - ."); // limpar
        i++;
    }

}

int diaMes (data tempo){
    if (tempo.tm_mon == 1 || tempo.tm_mon == 3 || tempo.tm_mon == 5 || tempo.tm_mon == 7 || tempo.tm_mon == 8 || tempo.tm_mon == 10 || tempo.tm_mon == 12)
        return 31;
    else if (tempo.tm_mon == 4 || tempo.tm_mon == 6 || tempo.tm_mon == 9 || tempo.tm_mon == 11)
        return 30;
    else if (tempo.tm_mon == 2){
        if(anoBi(tempo.tm_year))
            return 29;
        else 
            return 28;
    }
    else {
        return -1;
    }
}

int validDate (data *tempo, data hoje){
    int maxDias = diaMes(*tempo);

    if (maxDias == -1)
        return 0;
    else {
        if (tempo->tm_mday < 1 || tempo->tm_mday > maxDias){
            return 0;
        }

        // Esse ano
        if (tempo->tm_year == hoje.tm_year ){
            if (tempo->tm_mon == hoje.tm_mon){
                if (tempo->tm_mday >= hoje.tm_mday){
                    return 1;
                }
         
                return 0;
            }
            else if (tempo->tm_mon > hoje.tm_mon){
                return 1;
            }
             
            return 0;
        }
        // Prox ano
        if (tempo->tm_year == hoje.tm_year + 1){
            if (tempo->tm_mon == hoje.tm_mon){
                if (tempo->tm_mday < hoje.tm_mday){
                    return 1;
                }
         
                return 0;
            }

            else if (tempo->tm_mon < hoje.tm_mon){
                return 1;
            }
            return 0;
        }
        
    }
}

data atualData (){
    time_t sec = time(NULL);
    data atual = *localtime(&sec);
    atual.tm_mon += 1, atual.tm_year += 1900;

    return atual;
}

data opcConsulta(data consulta){
    data dia;
    dia.tm_mday = consulta.tm_mday;
    dia.tm_mon = consulta.tm_mon;
    dia.tm_year =consulta.tm_year;
    
    int result = 0;

    while (result == 0 || result > 6){
        dia.tm_mday -= 2;
        
        if (dia.tm_mday <= 0){
            dia.tm_mon -= 1;
            dia.tm_mday = diaMes(dia) + dia.tm_mday;
        }

        result = verificaData(dia.tm_mday, dia.tm_mon, dia.tm_year);
    }
    
    return dia;
}

int appointment(){
    data atual = atualData();
    data consulta;
    char consultIn[15];
    
    printf("\nInforme a data desejada para a consulta (DD/MM/AAAA): ");
    scanf("%s", consultIn);

    sepData(consultIn, &consulta);

    if (validDate(&consulta, atual)){
        int diaSemana = verificaData(consulta.tm_mday, consulta.tm_mon, consulta.tm_year);

        if (diaSemana == 1){
            printf("Não há atendimento aos domingos. Escolha outro dia.\n");
            sleep(2);
            printf("\e[H\e[2J");
            return appointment();
        }
        else if (diaSemana == 8){
            int choice = 0;
            data preFeriado = opcConsulta(consulta);

            printf("O dia escolhido é feriado.\n[1] - Podemos marcar para %d/%d/%d\n[2] - Escolher outro dia\n", preFeriado.tm_mday, preFeriado.tm_mon, preFeriado.tm_year);
            printf("Escolha: ");
            scanf("%d", &choice);
            
            if (choice == 1){
                // Marcar a Consulta
            }
            else if (choice == 2){
                return appointment();
            }
        }
        else{
            printf("A consulta foi marcada para o dia: %d/%d/%d\n", consulta.tm_mday, consulta.tm_mon, consulta.tm_year);
            return 1;
        }
    }
    else{
        printf("A data inserida é inválida. Tente novamente\n");
        sleep(4);
        printf("\e[H\e[2J");
        return appointment();
    }

    return -1;
}