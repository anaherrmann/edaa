/*Tomando como base a Atividade Avaliativa I, execute os mesmos testes utilizando a) a busca sequencial em uma lista ligada e b) em uma árvore binária de busca.

Para gerar uma árvore mais balanceada, utilize uma estratégia semelhante a escolha dos pivôs no QuickSort, isto é, inicie a raiz com o valor médio (n/2) e adicione os demais valores médios subdividindo os vetores esquerdo e direito e repetindo o processo. Ex.: 0 1 2 3 4 5 6 7 -> 3 1 0 2 5 4 6 7.

Compare os resultados com os já apresentados na Atividade anterior.*/


/*
1. Gerar listas ligadas de inteiros (1000;2000;5000;10000;100000)
2. Gerar arvores binarias de busca (1000;2000;5000;10000;100000)
3. Gerar vetores de numeros aleatorios para busca
4. Buscar nas listas ligadas
5. Buscar nas arvores de busca
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> 
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "./generate.c"

int buscar_lista(ListaLigada *lista, int buscado){
    NodoLista *nodo;
    for (nodo = lista->inicio; nodo != NULL; nodo = nodo->proximo){
        if(nodo->dado == buscado){
            return nodo->dado;
        }
    }
    return -1;
}

int buscar_arvore(NodoArvore *raiz, int buscado){
    if(raiz == NULL){
        return -1;
    }

    if(raiz->dado == buscado){
        return raiz->dado;
    }
    else if(raiz->dado > buscado){
        buscar_arvore(raiz->esquerda, buscado);
    }
    else{
        buscar_arvore(raiz->direita, buscado);
    }
}

double rodar_busca(ListaLigada *lista, NodoArvore *arvore, int buscado){
    int i, j;
    clock_t t;
    double tempo_geral = 0.0;
    double tempo_aux; 
    double tempo[10]; 

    for (i = 0; i < 10; i++)
    {
        t = clock(); 
        for (j = 0; j < 100; j++)
        {
            if(lista != NULL && arvore == NULL){
                buscar_lista(lista, buscado);
            }
            else if(lista == NULL && arvore != NULL){
                buscar_arvore(arvore, buscado);
            }
        }
        t = clock() - t; 
        tempo_aux = ((double)t); 
        tempo[i] = tempo_aux;        
    }
    
    for (i = 0; i < 10; i++)
    {
        tempo_geral += tempo[i];
    }

    return (tempo_geral/10);
    
}

double * chamar_busca_lista(ListaLigada *lista, int aleatorios[]){
    
    int i;
    static double resultado[4];
    double tempo_busca_aleatoria = 0.0;
    
    resultado[0] = rodar_busca(lista, NULL, 0); //busca primeiro elemento
    resultado[1] = rodar_busca(lista, NULL, ((lista->tamanho)-1)); // busca ultimo elemento
    resultado[2] = rodar_busca(lista, NULL, (lista->tamanho+1)); // busca elemento nao presente no array

    for(i = 0; i < 97; i++){
        tempo_busca_aleatoria += rodar_busca(lista, NULL, aleatorios[i]);
    }
    resultado[3] = (tempo_busca_aleatoria/97);

    printf("\nBUSCA COM %d\n", lista->tamanho);
    printf("%.3f\n", resultado[0]);
    printf("%.3f\n", resultado[1]);
    printf("%.3f\n", resultado[2]);
    printf("%.3f\n", resultado[3]);
    printf("\n\n");
    
    return resultado;
}

double * chamar_busca_arvore(NodoArvore *raiz, int aleatorios[], int tamanho){
    
    int i;
    static double resultado[4];
    double tempo_busca_aleatoria = 0;
    
    resultado[0] = rodar_busca(NULL, raiz, 0); //busca primeiro elemento
    resultado[1] = rodar_busca(NULL, raiz, tamanho-1); // busca ultimo elemento
    resultado[2] = rodar_busca(NULL, raiz, tamanho+1); // busca elemento nao presente no array
    for(i = 0; i < 97; i++){
        tempo_busca_aleatoria += rodar_busca(NULL, raiz, aleatorios[i]);
    }
    resultado[3] = (tempo_busca_aleatoria/97);

    printf("\nBUSCA COM %d\n", tamanho);
    printf("%.3f\n", resultado[0]);
    printf("%.3f\n", resultado[1]);
    printf("%.3f\n", resultado[2]);
    printf("%.3f\n", resultado[3]);
    printf("\n\n");
    
    return resultado;
}

int main(){
    ListaLigada *lista_um = criar_lista();
    gerar_lista(lista_um, 1000);
    ListaLigada *lista_dois = criar_lista();
    gerar_lista(lista_dois, 2000);
    ListaLigada *lista_cinco = criar_lista();
    gerar_lista(lista_cinco, 5000);
    ListaLigada *lista_dez = criar_lista();
    gerar_lista(lista_dez, 10000);
    ListaLigada *lista_cem = criar_lista();
    gerar_lista(lista_cem, 1000000);
    

    NodoArvore *arvore_um = gerar_arvore(0, 999);
    NodoArvore *arvore_dois = gerar_arvore(0, 1999);
    NodoArvore *arvore_cinco = gerar_arvore(0, 4999);
    NodoArvore *arvore_dez = gerar_arvore(0, 9999);
    NodoArvore *arvore_cem = gerar_arvore(0, 99999);


    int aleatorio_um[97];
    int aleatorio_dois[97];
    int aleatorio_cinco[97];
    int aleatorio_dez[97];
    int aleatorio_cem[97];

    int i;
    for(i = 0; i < 97; i++){
        aleatorio_um[i] = (rand() % 1000); 
        aleatorio_dois[i] = (rand() % 2000); 
        aleatorio_cinco[i] = (rand() % 5000); 
        aleatorio_dez[i] = (rand() % 10000); 
        aleatorio_cem[i] = (rand() % 100000); 
    }

    printf("Busca na Lista Ligada\n\n");
    double *um_ll = chamar_busca_lista(lista_um, aleatorio_um);
    double *dois_ll = chamar_busca_lista(lista_dois, aleatorio_dois);
    double *cinco_ll = chamar_busca_lista(lista_cinco, aleatorio_cinco);
    double *dez_ll = chamar_busca_lista(lista_dez, aleatorio_dez);
    double *cem_ll = chamar_busca_lista(lista_cem, aleatorio_cem);


    printf("Busca na Árvore Binária de Busca\n\n");
    double *um_ab = chamar_busca_arvore(arvore_um, aleatorio_um, 1000);
    double *dois_ab = chamar_busca_arvore(arvore_dois, aleatorio_dois, 2000);
    double *cinco_ab = chamar_busca_arvore(arvore_cinco, aleatorio_cinco, 5000);
    double *dez_ab = chamar_busca_arvore(arvore_dez, aleatorio_dez, 10000);
    double *cem_ab = chamar_busca_arvore(arvore_cem, aleatorio_cem, 100000);
}