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
    {"Caratinga",
     {{"Evento Cultural"}, {"Festa Junina"}, {"Evento de Caridade"}},
     {9.5, 7.8, 8.4}},
    {"Inhapim",
     {{"Festival de Verao"},
      {"Tarde de Sorvete"},
      {"Festival de Motocicletas"}},
     {9.0, 9.6, 8.0}},
    {"Ubaporanga",
     {{"Carnaval"}, {"Festival Cinema"}, {"Evento Geek"}},
     {7.5, 6.8, 7.2}},
    {"Belo Campo",
     {{"Musica Classica"}, {"Festival de Rock"}, {"Recital de Poesia"}},
     {9.7, 9.0, 9.2}},
    {"Ponte Nova",
     {{"Rodizio de Pizza"}, {"Jogo de Futebol"}, {"Parada Gay"}},
     {9.3, 7.4, 7.0}}};

typedef struct celula {
  TCidade item;
  struct celula *pai;
  struct celula *esq;
  struct celula *dir;
} TCelula;

typedef struct arvore {
  TCelula *raiz;
} TArvore;

void Central(TCelula *x) {
  if (x != NULL) {
    Central(x->esq);
    printf("Cidade: %s\n", x->item.nome);
    printf("Eventos:\n");
    for (int i = 0; i < 3; i++) { // 3 eventos por cidade
      printf("- %s, Nota %.2f\n", x->item.evento[i].nome, x->item.nota[i]);
    }
    Central(x->dir);
  }
}

void PreOrdem(TCelula *x) {
  if (x != NULL) {
    printf("Cidade: %s\n", x->item.nome);
    printf("Eventos:\n");
    for (int i = 0; i < 3; i++) {
      printf("- %s, Nota %.2f\n", x->item.evento[i].nome, x->item.nota[i]);
    }
    PreOrdem(x->esq);
    PreOrdem(x->dir);
  }
}

void PosOrdem(TCelula *x) {
  if (x != NULL) {
    PosOrdem(x->esq);
    PosOrdem(x->dir);
    printf("Cidade: %s\n", x->item.nome);
    printf("Eventos:\n");
    for (int i = 0; i < 3; i++) {
      printf("- %s, Nota %.2f\n", x->item.evento[i].nome, x->item.nota[i]);
    }
  }
}

TCelula *Pesquisar(TCelula *x, TCidade cidade) {
  if ((x == NULL) || (strcmp(x->item.nome, cidade.nome) == 0)) {
    return x;
  }
  if (strcmp(cidade.nome, x->item.nome) < 0) {
    return Pesquisar(x->esq, cidade);
  } else {
    return Pesquisar(x->dir, cidade);
  }
}

TCelula *Minimo(TCelula *x) {
  if (x == NULL) {
    return NULL;
  }
  while (x->esq != NULL) {
    x = x->esq;
  }
  return x;
}

TCelula *Maximo(TCelula *x) {
  if (x == NULL) {
    return NULL;
  }
  while (x->dir != NULL) {
    x = x->dir;
  }
  return x;
}

TCelula *criaNo(TCidade cidade) {
  TCelula *novoNo = (TCelula *)malloc(sizeof(TCelula));
  if (novoNo == NULL) {
    printf("Erro ao alocar memória!\n");
    return NULL;
  }
  novoNo->item = cidade;
  novoNo->pai = NULL;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  return novoNo;
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

void menuOrdenacao(){
  printf("\nMENU:\n");
  printf("1 - Selection\n");
  printf("2 - Insertion\n");
  printf("3 - Shellsort\n");
  printf("4 - Heapsort\n");
  printf("5 - Quicksort\n");
  printf("6 - Bubblesort\n");
  printf("7 - Mergesort\n");
}

//------------------------------------------- CODIGOS DE ALGORITMO DE ORDENHAÇÃO -------------------------------------------

void Selecao(TCidade *A, int n){
  int i, j, Min;
  TCidade x;
  for(i = 1; i <= n; j++){
    Min = i;
    if(A[j].nota > A[Min].nota){ //Trocar ordem - TROCADO
      Min = j;
    }
    // Movimentação
    x = A[Min];
    A[Min] = A[i];
    A[i] = x;
  }
}

// ------------------------------------------- INSERTION -------------------------------------------

void Insercao(TCidade *A, int n){
  int i, j;
  TCidade x;
  for(i = 2; i <= n; i++){
    x = A[i];
    j = i - 1;
    A[0] = x; /* Sentinela */
    while(x.nota > A[j].nota){ //Trocar ordem - TROCADO
      A[j+1] = A[j]; //Movimentação
      j--;
    }
    A[j+1] = x; //Inserção
  }
}

// ------------------------------------------- SHELLSORT -------------------------------------------

void Shellsort(TCidade *A, int n){
  int i, j;
  int h = 1;
  TCidade x;
  do{
    h = h * 3 + 1;
  }while(h < n);
  do{
    h /= 3;
    for(i = h + 1; i <= n; i++){
      x = A[i];
      j = i;
      while (A[j-h].nota < x.nota){ //Trocar ordem - TROCADO
        A[j] = A[j-h];
        j -= h;
        if(j <= h){
          goto L999;
        }
      }
      L999: A[j] = x;
    }
  } while(h != 1);
}

// ------------------------------------------- HEAPSORT -------------------------------------------

void MaxHeapify(TCidade *A, int i, int n){
  TCidade aux;
  int esq = 2 * i;
  int dir = 2 * i + 1;
  int maior;
  if( (A[i].nota > A[esq].nota) && (esq <= n) && (esq >= 1) ){ //Trocar ordem - TROCADO
    maior = esq;
  } else{
    maior = i;
  }
  if( (A[maior].nota > A[dir].nota) && (dir <= n) && (dir >= 1) ){ //Trocar ordem - TROCADO
    maior = dir;
  }
  if(maior != i){
    aux = A[maior];
    A[maior] = A[i];
    A[i] = aux;
    MaxHeapify(A, maior, n);
  }
}

void BuildMaxHeap(TCidade *A, int n){
  int i;
  for(i = n/2; i > 0; i--){
    MaxHeapify(A, i, n);
  }
}

void HeapSort(TCidade *A, int n){
  TCidade aux;
  int tam = n;
  int i;
  BuildMaxHeap(A, n);
  for(i = 1; i <= n - 1; i++){
    aux = A[1];
    A[1] = A[tam];
    A[tam] = aux;
    tam--;
    MaxHeapify(A, 1, tam);
  }
}

// ------------------------------------------- QUICKSORT -------------------------------------------
int Particao(TCidade *A, int p, int r){
  TCidade x, Aux;
  int i, j;
  x = A[r];
  i = p - 1;
  for(j = p; j < r; j++){
    if(A[j].nota <= x.nota){ //Controla crescente/decrescente
      i = i + 1;
      Aux = A[i];
      A[i] = A[j];
      A[j] = Aux;
    }
  }
  Aux = A[i + 1];
  A[i + 1] = A[r];
  A[r] = Aux;
  return i + 1;
}

void Quicksort(TCidade *A, int p, int r){
  int q;
  if(p < r){
    q = Particao(A, p, r);
    Quicksort(A, p, q - 1);
    Quicksort(A, q + 1, r);
  }
}

// ------------------------------------------- BUBBLESORT -------------------------------------------

void Bubblesort(TCidade A[], int n){
  TCidade x;
  int i, j;
  for(i = 1; i < n; i++){
      for(j = n; j > i; j--){
          if(A[j].nota < A[j - 1].nota){ //Trocar ordem - TROCADO
              x = A[j];
              A[j] = A[j - 1];
              A[j - 1] = x;
          }
      }
    }
}

// ------------------------------------------- MERGESORT -------------------------------------------

void Merge(TCidade *A, int l, int m, int r, int nota) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  // Criando arrays temporários para armazenar as cidades
  TCidade L[n1], R[n2];

  // Copiando os dados para os arrays temporários
  for (i = 0; i < n1; i++) {
      L[i] = A[l + i];
  }
  for (j = 0; j < n2; j++) {
      R[j] = A[m + 1 + j];
  }

  // Juntando os arrays ordenados de volta no vetor original
  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {
      if (L[i].nota[nota] <= R[j].nota[nota]) { //Trocar ordem - TROCADO
          A[k] = L[i];
          i++;
      } else {
          A[k] = R[j];
          j++;
      }
      k++;
  }

  // Copiando os elementos restantes de L[], se houver
  while (i < n1) {
      A[k] = L[i];
      i++;
      k++;
  }

  // Copiando os elementos restantes de R[], se houver
  while (j < n2) {
      A[k] = R[j];
      j++;
      k++;
  }
}

void MergeSort(TCidade *A, int l, int r, int nota) {
  if (l < r) {
      int m = l + (r - l) / 2;

      // Ordena as metades
      MergeSort(A, l, m, nota);
      MergeSort(A, m + 1, r, nota);

      // Junta as metades ordenadas
      Merge(A, l, m, r, nota);
  }
}

// ------------------------------------------------------------------------------------------------

int main(){

    TArvore arvore;
    arvore.raiz = NULL;
    TCidade PesquisarCidade;
    char PesquisarNome[25];

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
            case 4:
                printf("Insira o nome da cidade: ");
                scanf("%s", PesquisarNome);

                strcpy(PesquisarCidade.nome, PesquisarNome);

                TCelula *r = Pesquisar(arvore.raiz, PesquisarCidade);

                if(r != NULL){
                    printf("\n Cidade encontrada: %s\n", r->item.nome);
                    printf("Eventos:\n");
                    for(int i = 0; i < 3; i++){
                        printf("- %s, Nota %.2f\n", r->item.evento[i].nome, r->item.nota[i]);
                    }
                } else{
                    printf("Cidade nao encontrada!\n");
                }
                break;
            case 10:
                printf("Saindo do Programa..\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 10);
    
    return 0;
}
