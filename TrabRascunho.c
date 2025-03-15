#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct evento {
    char nome[50];
} TEvento;

typedef struct cidade {
    char nome[25];
    TEvento evento[3]; // Lista de eventos
    double nota[3];
} TCidade;

TCidade cidades[5] = {
    {"Caratinga", {{"Evento Cultural"}, {"Festa Junina"}, {"Evento de Caridade"}}, {9.5, 7.8, 8.4}},
    {"Inhapim", {{"Festival de Verao"}, {"Tarde de Sorvete"}, {"Festival de Motocicletas"}}, {9.0, 9.6, 8.0}},
    {"Ubaporanga", {{"Carnaval"}, {"Festival Cinema"}, {"Evento Geek"}}, {7.5, 6.8, 7.2}},
    {"Belo Campo", {{"Musica Classica"}, {"Festival de Rock"}, {"Recital de Poesia"}}, {9.7, 9.0, 9.2}},
    {"Ponte Nova", {{"Rodizio de Pizza"}, {"Jogo de Futebol"}, {"Parada Gay"}}, {9.3, 7.4, 7.0}}
};

typedef struct celula {
    TCidade item;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
} TCelula;

typedef struct arvore {
    TCelula *raiz;
} TArvore;

void Central(TCelula *x){
    if (x != NULL){
        Central(x->esq);
        printf("Cidade: %s\n", x->item.nome);
        printf("Eventos:\n");
        for(int i = 0; i < 3; i++){  // 3 eventos por cidade
            printf("- %s, Nota %.2f\n", x->item.evento[i].nome, x->item.nota[i]);
        }
        Central(x->dir);
    }
}

void PreOrdem(TCelula *x){
    if(x != NULL){
        printf("Cidade: %s\n", x->item.nome);
        printf("Eventos:\n");
        for(int i = 0; i < 3; i++){
            printf("- %s, Nota %.2f\n", x->item.evento[i].nome, x->item.nota[i]);
        }
        PreOrdem(x->esq);
        PreOrdem(x->dir);
    }
}

void PosOrdem(TCelula *x){
    if(x != NULL){
        PosOrdem(x->esq);
        PosOrdem(x->dir);
        printf("Cidade: %s\n", x->item.nome);
        printf("Eventos:\n");
        for(int i = 0; i < 3; i++){
            printf("- %s, Nota %.2f\n", x->item.evento[i].nome, x->item.nota[i]);
        }
    }
}

TCelula* Pesquisar(TCelula *x, TCidade cidade){
    if((x == NULL) || (strcmp(x->item.nome, cidade.nome) == 0)){
        return x;
    }
    if(strcmp(cidade.nome, x->item.nome) < 0){
        return Pesquisar(x->esq, cidade);
    } else{
        return Pesquisar(x->dir, cidade);
    }
}

TCelula* Minimo(TCelula *x){
    if(x == NULL){
        return NULL;
    }
    while(x->esq != NULL){
        x = x->esq;
    }
    return x;
}

TCelula* Maximo(TCelula *x){
    if(x == NULL) {
        return NULL;
    }
    while(x->dir != NULL){
        x = x->dir;
    }
    return x;
}

TCelula* criaNo(TCidade cidade){
    TCelula *novoNo = (TCelula*) malloc(sizeof(TCelula));
    if(novoNo == NULL){
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    novoNo->item = cidade;
    novoNo->pai = NULL;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

void Inserir(TCelula **x, TCelula *pai, TCidade cidade){
    if ((*x) == NULL){
        (*x) = criaNo(cidade);
        if (pai != NULL){
            (*x)->pai = pai;
        }
        return;
    }
    if(strcmp((*x)->item.nome, cidade.nome) > 0){
        Inserir(&(*x)->esq, (*x), cidade);
        return;
    }
    if(strcmp((*x)->item.nome, cidade.nome) <= 0){
        Inserir(&(*x)->dir, (*x), cidade);
    }
}

void menu(){
    printf("\nMENU:\n");
    printf("1 - Imprimir Arvore (Caminhamento Central)\n");
    printf("2 - Imprimir Arvore (Pre-Ordem)\n");
    printf("3 - Imprimir Arvore (Pos-Ordem)\n");
    printf("4 - Pesquisar Cidade\n");
    printf("10 - Sair do Programa\n\n");
    printf("Escolha uma opcao: ");
}

int main(int argc, char const *argv[]){

    TArvore arvore;
    arvore.raiz = NULL;

    // Inserindo as cidades pré-definidas automaticamente na árvore
    for(int i = 0; i < 5; i++){
        Inserir(&arvore.raiz, NULL, cidades[i]);
    }

    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Impressao em Ordem Central:\n");
                Central(arvore.raiz);
                break;
            case 2:
                printf("Impressao em Pre-Ordem:\n");
                PreOrdem(arvore.raiz);
                break;
            case 3:
                printf("Impressao em Pos-Ordem:\n");
                PosOrdem(arvore.raiz);
                break;
            case 10:
                printf("Saindo do Programa..\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 10);
    
    return 0;
}
