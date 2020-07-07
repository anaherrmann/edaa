/*
Um deque (double-ended queue) é uma estrutura de dados com as operações: 
insere_inicio
insere_fim
remove_inicio
remove_fim.
Implemente um deque utilizando listas ligadas.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    struct no *anterior;
    struct no *proximo;
} no;

typedef struct deque
{
    no *inicio;
} deque;

int insere_inicio(deque *deque, int dado){    
    no *novo;
    novo = malloc(sizeof(no));
    if(novo != NULL){
        novo->dado = dado;
        novo->proximo = deque->inicio;
        novo->anterior = deque->inicio->anterior;
        deque->inicio = novo;
        deque->inicio->proximo = novo->proximo;
        deque->inicio->anterior = novo->anterior;
        return 1;
    }
    return -1;   
}

int insere_fim(deque *deque, int dado){
    no *novo;
    novo = malloc(sizeof(no));
    novo->dado = dado;
    novo->proximo = deque->inicio;
    novo->anterior = deque->inicio->anterior;
    deque->inicio->anterior = novo;
    novo->anterior->proximo = novo;
    return 1;
}

int remove_inicio(deque *deque){
    if(deque->inicio->proximo == deque->inicio){
        return -1; 
    }
    no *remover = deque->inicio->proximo;
    deque->inicio->proximo = remover->proximo;
    remover->proximo->anterior = deque->inicio;
    free(remover);
    return 1;
}

int remove_fim(deque *deque){
    if(deque->inicio->proximo == deque->inicio){
        return -1; 
    }
    no *remover = deque->inicio->anterior;
    deque->inicio->anterior = remover->anterior;
    remover->anterior->proximo = deque->inicio;
    free(remover);
    return 1;
}


deque *cria_deque(deque* d){    
    d = malloc(sizeof(deque));
    d->inicio = malloc(sizeof(no));
    d->inicio->proximo = d->inicio;
    d->inicio->anterior = d->inicio;
    return d;
}

int main(){
    deque *deq = cria_deque(deq);
    insere_inicio(deq, 5);
    insere_fim(deq, 6);
    remove_inicio(deq);
    remove_fim(deq);
}


