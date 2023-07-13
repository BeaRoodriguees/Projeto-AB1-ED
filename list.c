#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define 1 TRUE
#define 0 FALSE

// definir nomes melhores
// implementar funções: removerRepetido, removerElemRepetido e qntRepetido

typedef struct{
    char nome[60];
    int idade;
    int cpf;
} Elem;

typedef struct{
    Elem *elementos;
    int qnt, tam;
} ListaE;

int criarLista (ListaE *lista, int tamanho){
    lista->elementos = calloc(tam, sizeof(Elem));

    if (lista->elementos == NULL) return FALSE;

    lista->tam = tamanho;
    lista->qnt = 0;

    return TRUE;
}

int vaziaLista (ListaE lista){
    return lista.qnt == 0;
}

int cheiaLista (ListaE lista){
    return lista.qnt == lista.tam;
}

int quantidade (ListaE lista){
    return lista.quantidade;
}

int qntRepetido (ListaE lista){
}

int inserirInicio (ListaE *lista, Elem novo){
    if (cheiaLista(*lista)) return FALSE;

    for (int i = lista->qnt; i > 0; i--){
        lista->elementos[i] = lista->elementos[i-1];
    }

    lista->elementos[0] = novo;
    lista->qnt++;
    return TRUE;
}

int inserirFim (ListaE *lista, Elem novo){
    if (cheiaLista(*lista)) return FALSE;

    lista->elementos[lista->quantidade++] = novo;
    return TRUE;
}

void imprimirLista (ListaE lista){
    for (int i = 0; i < lista.qnt; i++){
        printf("O paciente é %s, de %d anos, com CPF %d.\n", lista.elementos[i].nome, lista.elementos.idade, lista.elementos.cpf);
    }
}

int pesquisarElem (ListaE lista, char *nome){
    for (int i = 0; i < lista.qnt; i++){
        if (strcmp(lista.elementos[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int removerInicio (ListaE *lista, Elem *elem){
    if (vaziaLista(*lista)) return FALSE;

    *elem = lista->elementos[0];
    --lista->qnt;

    for (int i = 0; i < lista->qnt; i++){
        lista->elementos[i] = lista->elementos[i+1];
    }

    return TRUE;
}

int removerFim (ListaE *lista, Elem *elem){
    if(vaziaLista(*lista)) return FALSE;

    *elem = lista->elementos[--lista->qnt];
    return TRUE;
}

int remover (ListaE *lista, Elem *elem){
    int pos = pesquisarElem(*lista, elem->nome);
    
    if (pos < 0) return FALSE;

    *elem = lista->elementos[pos];

    for (int i = pos; i < lista.qnt; i++)
        lista->elementos[i] = lista->elementos[i+1];

    lista->qnt--;

    return TRUE;
}

void removerRepetido (){
}

int removerElemRepetido (ListaE *lista, char elem){
}
