#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG if(1) printf

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

int validDate (char *in, data *tempo, data hoje){
    sepData(in, tempo);
    data aux = *tempo;
    int maxDias = diaMes(aux);

    if (maxDias == -1)
        return 0;
    else {
        if (tempo->tm_mday < 1 || tempo->tm_mday > maxDias){
            DEBUG ("a\n");
            return 0;
        }

        // Esse ano
        if (tempo->tm_year == hoje.tm_year ){
            DEBUG ("entrou ano =\n");

            if (tempo->tm_mon == hoje.tm_mon){
                DEBUG ("entrou mes ==\n");

                if (tempo->tm_mday >= hoje.tm_mday){
                    return 1;
                }
         
                return 0;
            }

            else if (tempo->tm_mon > hoje.tm_mon){
                DEBUG ("entrou mes =!\n");

                return 1;
            }
             
            return 0;
        }

        if (tempo->tm_year == hoje.tm_year + 1){
            DEBUG ("entrou ano = +1\n");

            if (tempo->tm_mon == hoje.tm_mon){
                DEBUG ("entrou mes == +1\n");

                if (tempo->tm_mday < hoje.tm_mday){
                    return 1;
                }
         
                return 0;
            }

            else if (tempo->tm_mon < hoje.tm_mon){
                DEBUG ("entrou mes =! +1\n");

                return 1;
            }
             
            return 0;
        }
        
    }
}

data atualData (data atual){
    time_t sec = time(NULL);
    atual = *localtime(&sec);
    atual.tm_mon += 1, atual.tm_year += 1900;

    return atual;
}

int main(){
    data atual = atualData(atual);

    data consulta;
    char consultIn[15];

    
    while(1){
        printf("Informe a data desejada para a consulta (DD/MM/AAAA): ");
        scanf("%s", consultIn);

        if(validDate(consultIn, &consulta, atual)){
            break;
        }
        printf("Dada inválida. ");
    }

    printf("Data de Hoje: %d/%d/%d\n", atual.tm_mday, atual.tm_mon, atual.tm_year);
    printf("Data da Consulta: %d/%d/%d\n", consulta.tm_mday, consulta.tm_mon, consulta.tm_year);
}