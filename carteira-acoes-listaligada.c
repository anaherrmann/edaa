/*Um investidor deseja armazenar as ações que possui na carteira em uma lista dinâmica. 
Cada ação é representada por um código alfanumérico (VALE3, PETR4, etc.), 
a quantidade, o valor de compra e o valor atual. São funcionalidades importantes para o investidor:
a) Inserir ações na carteira;
b) Vender ações ou parte delas;
b) Buscar uma ação por código;
c) Listar as ações por código (ordenado);
d) Determinar a posição financeira da carteira, i.e., quanto de lucro ou prejuízo em reais e em porcentagem para cada ação e considerando a carteira atual.
 
Escreva um programa para o investidor com exemplos de uso das funcionalidades. 
i) A linguagem de programação é livre; 
ii) O algoritmo de ordenação deve ser implementado (qualquer um);
iii) A interface gráfica ou a leitura de dados de entrada não é necessária.*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tamanho_codigo = 5;
typedef struct acao
{
    char *codigo;
    double valor_compra;
    double valor_atual;
    int quantidade;
    struct acao *proximo;
} acao;
 
typedef struct carteira
{
    struct acao *inicio;
    int tamanho;
} carteira;
int compara_codigos(char codigo_um[], char codigo_dois[], int indice){
    if(indice > tamanho_codigo){
        return 1;
    }

    if(codigo_um[indice] > codigo_dois[indice]){
        return 1;
    }
    else if(codigo_um[indice] < codigo_dois[indice]){
        return 2;
    }
    else {
        return compara_codigos(codigo_um, codigo_dois, indice++);
    }
}

acao *ordenar_vetor(acao *inicio_lista_um, acao *inicio_lista_dois){
    acao *resultado = NULL;
    if(inicio_lista_um == NULL){
        return (inicio_lista_dois);
    }
    else if(inicio_lista_dois == NULL) {
        return (inicio_lista_um);
    }


    int maior = compara_codigos(inicio_lista_um->codigo, inicio_lista_dois->codigo, 0);
    if(maior == 2){ 
        resultado = inicio_lista_um;
        resultado->proximo = ordenar_vetor(inicio_lista_um->proximo, inicio_lista_dois);
    } 
    else {
        resultado = inicio_lista_dois;
        resultado->proximo = ordenar_vetor(inicio_lista_um, inicio_lista_dois->proximo);
    } 
    
    return (resultado);
}

void descobre_inicio_meio(acao *inicio, acao **inicio_lista_um, acao **inicio_lista_dois){
    acao *percorre_devagar;
    acao *percorre_rapido;

    percorre_devagar = inicio;
    percorre_rapido = inicio->proximo;

    for(percorre_rapido; percorre_rapido->proximo != NULL; percorre_rapido = percorre_rapido->proximo){

        percorre_rapido = percorre_rapido->proximo;
        percorre_devagar = percorre_devagar->proximo;

    }

    *inicio_lista_um = inicio;
    *inicio_lista_dois = percorre_devagar;
    percorre_devagar = NULL; 
    // o erro acontece por causa dessa definicao aqui, 
    // que deveria dividir as duas partes do vetor
    // mas ao inves disso perde o ponteiro e gera segmentation fault

}


void merge_sort(acao **inicio_lista){
    acao *inicio = *inicio_lista;
    acao *inicio_lista_um;
    acao *inicio_lista_dois;

    if(inicio != NULL && inicio->proximo != NULL){
        descobre_inicio_meio(inicio, &inicio_lista_um, &inicio_lista_dois);
        merge_sort(&inicio_lista_um);
        merge_sort(&inicio_lista_dois);
    }
    return;
}

void posicao(carteira *carteira_cliente){
    if(carteira_cliente->inicio == NULL){
        return;
    }

    acao *acao_atual;
    double porcentagem;
    double diferenca;

    for(acao_atual = carteira_cliente->inicio; acao_atual != NULL; acao_atual = acao_atual->proximo){
        printf("Codigo: %s\n", acao_atual->codigo);
        printf("Quantidade: %d\n", acao_atual->quantidade);
        printf("Valor de compra: %.2f\n", acao_atual->valor_compra);
        printf("Valor atual: %.2f\n", acao_atual->valor_atual);
        if(acao_atual->valor_compra < acao_atual->valor_atual){
            // lucro
            porcentagem = 100-((acao_atual->valor_compra/acao_atual->valor_atual)*100);
            diferenca = (acao_atual->valor_atual - acao_atual->valor_compra) * acao_atual->quantidade;
            printf("Aumento de %.1f\%(R$%.2f) no valor da carteira\n", porcentagem, diferenca);
        } else if(acao_atual->valor_compra > acao_atual->valor_atual){
            porcentagem = 100-((acao_atual->valor_atual/acao_atual->valor_compra)*100);
            diferenca = (acao_atual->valor_compra - acao_atual->valor_atual) * acao_atual->quantidade;
            printf("Prejuizo de %.1f\%(R$%.2f) no valor da carteira\n", porcentagem, diferenca);
        } else {
            printf("Nao ha diferenca entre os valores de compra e venda.\n");
        }
        printf("\n");
    }
}
 
void listar(carteira *carteira_cliente){
    if(carteira_cliente->inicio == NULL){
        return;
    }

   // merge_sort(&(carteira_cliente->inicio));

    acao *acao_atual;
    printf("Acoes da carteira\n");
    for(acao_atual = carteira_cliente->inicio; acao_atual != NULL; acao_atual = acao_atual->proximo){
        printf("Codigo: %s\n", acao_atual->codigo);
        printf("Quantidade: %d\n", acao_atual->quantidade);
        printf("Valor compra: %.2f\n", acao_atual->valor_compra);
        printf("Valor atual: %.2f\n", acao_atual->valor_atual);
        printf("\n\n");
    }
}
 
acao *buscar(carteira *carteira_cliente, char codigo_buscado[]){
    if(carteira_cliente->inicio == NULL){
        return NULL;
    }

    acao *acao_atual;
    for(acao_atual = carteira_cliente->inicio; acao_atual != NULL; acao_atual = acao_atual->proximo){
        if(strcmp(acao_atual->codigo, codigo_buscado) == 0){

            return acao_atual;
        }
    }

    return NULL;
}
 
int vender(carteira *carteira_cliente, char codigo_buscado[], int quantidade_venda){
    acao *acao_atual;

    if(carteira_cliente->inicio == NULL){
        return -1;
    }

    if(strcmp(carteira_cliente->inicio->codigo, codigo_buscado) == 0){    
        if(carteira_cliente->inicio->quantidade == quantidade_venda){
            acao *auxiliar;
            auxiliar = carteira_cliente->inicio;
            
            carteira_cliente->inicio = carteira_cliente->inicio->proximo;
            free(auxiliar);
            return 1;
        }  else if(quantidade_venda > carteira_cliente->inicio->quantidade){
            return -1;
        }  else {
             carteira_cliente->inicio->quantidade = carteira_cliente->inicio->quantidade - quantidade_venda;
             return 1;
        }
        
    }

    for(acao_atual = carteira_cliente->inicio; acao_atual != NULL; acao_atual = acao_atual->proximo){
        if(strcmp(acao_atual->proximo->codigo, codigo_buscado) == 0){
            if(acao_atual->proximo->quantidade == quantidade_venda){
                acao *auxiliar;
                auxiliar = acao_atual->proximo;
                acao_atual->proximo = acao_atual->proximo->proximo;
                free(auxiliar);
                return 1;
            }  else if(quantidade_venda > carteira_cliente->inicio->quantidade){
                return -1;
            }  else {
                acao_atual->proximo->quantidade = acao_atual->proximo->quantidade - quantidade_venda;
                return 1;
            }
        }
    }
    return -1;
 
}
 
int inserir(carteira *carteira_cliente, char codigo[], double valor_compra, double valor_atual, int quantidade){
    acao *nova_acao;
    nova_acao = malloc(sizeof(acao));
 
    if (nova_acao != NULL) {
 
        nova_acao->codigo = codigo;
        nova_acao->valor_atual = valor_atual;
        nova_acao->valor_compra = valor_compra;
        nova_acao->quantidade = quantidade;
        nova_acao->proximo = carteira_cliente->inicio;
        carteira_cliente->inicio = nova_acao;
        carteira_cliente->tamanho++;
 
        return carteira_cliente->tamanho-1;
    }
    
    return -1;
}
 
carteira *iniciar_carteira(){
    carteira *carteira = malloc(sizeof(carteira));
    carteira->inicio = NULL;
    carteira->tamanho = 0;
    return carteira;
}
 
int main(){ 
    carteira *carteira_cliente;
    carteira_cliente = iniciar_carteira();
    
    inserir(carteira_cliente, "PEDQ5", 16.6, 18.7, 20);
    inserir(carteira_cliente, "AABB2", 20.9, 20.9, 10);
    inserir(carteira_cliente, "VITO6", 19.9, 16.7, 10);
    inserir(carteira_cliente, "LGBT4", 13.13, 26.26, 13);
    inserir(carteira_cliente, "L4D22", 10.9, 14.7, 11);
    inserir(carteira_cliente, "KTDE2", 14.9, 18.7, 11);
    vender(carteira_cliente, "VITO6", 5);
    acao *acao_cliente = buscar(carteira_cliente, "VITO6");
    listar(carteira_cliente); // FUNCAO COM ERRO - NAO ORDENA - verificar funcao descobre_inicio_meio()
    posicao(carteira_cliente);
}
