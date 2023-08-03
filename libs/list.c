#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// definir nomes melhores
// implementar funções: removerRepetido

typedef struct elem{
    char nome[60];
    int idade;
    int cpf_i;
    char cpf_c[12];
} Elem;

typedef struct lista{
    Elem *elementos;
    int qnt, tam;
} ListaE;

int criarLista (ListaE *lista, int tamanho){
    lista->elementos = calloc(tamanho, sizeof(Elem));

    if (lista->elementos == NULL) return FALSE;

    lista->tam = tamanho;
    lista->qnt = 0;

    return TRUE;
}

int verVazia (ListaE lista){
    return lista.qnt == 0;
}

int verCheia (ListaE lista){
    return lista.qnt == lista.tam;
}

int inInicio (ListaE *lista, Elem novo){
    if (verCheia(*lista)) return FALSE;

    for (int i = lista->qnt; i > 0; i--){
        lista->elementos[i] = lista->elementos[i-1];
    }

    lista->elementos[0] = novo;
    lista->qnt++;
    return TRUE;
}

int inFim (ListaE *lista, Elem novo){
    if (verCheia(*lista)) return FALSE;

    lista->elementos[lista->qnt++] = novo;
    return TRUE;
}

void imprimirLista (ListaE lista){
    for (int i = 0; i < lista.qnt; i++){
        printf("O paciente é %s, de %d anos, com CPF %d.\n", lista.elementos[i].nome, lista.elementos[i].idade, lista.elementos[i].cpf_i);
    }
}

int pesquisarNome (ListaE lista, char *nome){
    for (int i = 0; i < lista.qnt; i++){
        if (strcmp(lista.elementos[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int pesquisarCPF (ListaE lista, int cpf_i){
    for (int i = 0; i < lista.qnt; i++){
        if (lista.elementos[i].cpf_i == cpf_i)
            return i;
    }
    return -1;
}

int qnt (ListaE lista){
    return lista.qnt;
}

int removerInicio (ListaE *lista, Elem *elem){
    if (verVazia(*lista)) return FALSE;

    *elem = lista->elementos[0];
    --lista->qnt;

    for (int i = 0; i < lista->qnt; i++){
        lista->elementos[i] = lista->elementos[i+1];
    }

    return TRUE;
}

int removerFim (ListaE *lista, Elem *elem){
    if(verVazia(*lista)) return FALSE;

    *elem = lista->elementos[--lista->qnt];
    return TRUE;
}

int remover (ListaE *lista, int pos){    
    if (pos < 0) return FALSE;

    for (int i = pos; i < lista->qnt; i++)
        lista->elementos[i] = lista->elementos[i+1];

    lista->qnt--;

    return TRUE;
}

void qntElem (ListaE lista){
    int cont = 0;
    while(!verVazia(lista)){
        int check = lista.elementos[0].cpf_i;
       
        while (pesquisarCPF(lista, check) != -1){
            int pos = pesquisarCPF(lista, check);
            cont++;
            remover(&lista, pos);
        }

        printf("Contém %d unidade(s) do elemento %d\n", cont, check);
        cont = 0;
    }
}

void removerElemRepetido (ListaE *lista, int item){
    int count = 0;
    for (int i = 0; i < lista->qnt; i++){
        if (lista->elementos[i].cpf_i == item){
            count++;
       
            if (count >= 2){
                for (int j = i; j < lista->qnt; j++){
                    lista->elementos[j] = lista->elementos[j+1];
                }

                lista->qnt--;
            }
        }
    }
}

void removerElem (ListaE *lista, int item){
    for (int i = 0; i < lista->qnt; i++){
        if (lista->elementos[i].cpf_i == item){
            for (int j = i; j < lista->qnt; j++){
                lista->elementos[j] = lista->elementos[j+1];
            }
            lista->qnt--;
        }
    }
}

void removerRepetidos (ListaE *lista){
    for (int i = 0; i < lista->qnt; i++){
        for (int j = i + 1; j < lista->qnt; j++){
            if (lista->elementos[i].cpf_i == lista->elementos[j].cpf_i){
                    for (int k = j; k < lista->qnt; k++)
                        lista->elementos[k] = lista->elementos[k+1];
                    
                    lista->qnt--;
            }
        }
    }
}

void inverterLista (ListaE *lista){
    ListaE copia;
    criarLista(&copia, lista->tam);
    copia.qnt = lista->qnt;
    copia.tam = lista->tam;

    for (int i = 0; i < lista->qnt; i++){
        copia.elementos[i] = lista->elementos[lista->qnt-i-1] ;
    }

    for (int i = 0; i < lista->qnt; i++){
        lista->elementos[i] = copia.elementos[i] ;
    }

    free(copia.elementos);
    
}