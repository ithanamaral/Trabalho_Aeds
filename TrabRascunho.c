#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct evento {
  char nome[50];
} TEvento;

typedef struct cidade {
  char nome[25];
  TEvento evento[3]; // Lista de eventos
  float nota[3];
} TCidade;

TCidade cidades[7] = {
    {"Anliy City",
      {{"Curso de Japones"}, {"Rodizio de Sushi"}, {"Conhecendo o Goku"}},
      {0, 0, 0}},
    {"Belem",
      {{"Escalar Montanha"}, {"Bungee Jump"}, {"Paraquedismo"}},
      {0, 0, 0}},
    {"Caratinga",
     {{"Evento Cultural"}, {"Festa Junina"}, {"Evento de Caridade"}},
     {0, 0, 0}},
    {"Campo Belo",
     {{"Musica Classica"}, {"Festival de Rock"}, {"Recital de Poesia"}},
     {0, 0, 0}},
    {"Inhapim",
     {{"Festival de Verao"}, {"Tarde de Sorvete"}, {"Festival de Motocicletas"}},
     {0, 0, 0}},
    {"Ponte Nova",
     {{"Rodizio de Pizza"}, {"Jogo de Futebol"}, {"Parada Gay"}},
     {0, 0, 0}},
    {"Ubaporanga",
     {{"Carnaval"}, {"Festival Cinema"}, {"Evento Geek"}},
     {0, 0, 0}}
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

void Inserir(TCelula **x, TCelula *pai, TCidade A) {
  if ((*x) == NULL) {
      (*x) = criaNo(A);
      if (pai != NULL)
          (*x)->pai = pai;
      return;
  }

  if ((*x)->item.nota > A.nota) {
      Inserir(&(*x)->esq, (*x), A);
      return;
  }

  if ((*x)->item.nota <= A.nota) {
      Inserir(&(*x)->dir, (*x), A);
  }
}

void gerarNotas() {
  //Foi necessário essa função porque em C não dá pra colocar o rand dentro de TCidades
  for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 3; j++) {
          cidades[i].nota[j] = (rand() % 101) / 10.0;
      }
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

void menuOrdenacoes(){
  printf("\nEscolha o metodo:\n");
      printf("1 - Selection\n");
      printf("2 - Insertion\n");
      printf("3 - Shellsort\n");
      printf("4 - Heapsort\n");
      printf("5 - Quicksort\n");
      printf("6 - Bubblesort\n");
      printf("7 - Mergesort\n");
}


//------------------------------------------- CODIGOS DE ALGORITMO DE ORDENHAÇÃO -------------------------------------------

void Selecao(float *A, int n) {
  int i, j, Min;
  float x;
  for(i = 0; i < n - 1; i++) {
    Min = i;
    for (j = i + 1; j < n; j++) {
      if (A[j] > A[Min]) { // Troca ordem para ordenar de forma decrescente
        Min = j;
      }
    }
    // Movimentação
    x = A[Min];
    A[Min] = A[i];
    A[i] = x;
  }
}


// ------------------------------------------- INSERTION -------------------------------------------

void Insercao(float *A, int n) {
  int i, j;
  float x;
  for(i = 1; i < n; i++) {
    x = A[i];
    j = i - 1;
    while (j >= 0 && A[j] < x) { // Troca ordem
      A[j + 1] = A[j];  // Movimentação
      j--;
    }
    A[j + 1] = x; // Inserção
  }
}



// ------------------------------------------- SHELLSORT -------------------------------------------

void Shellsort(float *A, int n) {
  int i, j, h = 1;
  float x;
  do {
    h = h * 3 + 1;
  } while (h < n);
  
  do {
    h /= 3;
    for(i = h; i < n; i++) {
      x = A[i];
      j = i;
      while (j >= h && A[j - h] < x) { // Troca ordem
        A[j] = A[j - h];
        j -= h;
      }
      A[j] = x;
    }
  } while (h > 1);
}


// ------------------------------------------- HEAPSORT -------------------------------------------

void MaxHeapify(float *A, int i, int n) {
  int esq = 2 * i + 1, dir = 2 * i + 2, maior;
  
  if (esq < n && A[esq] > A[i]) {
    maior = esq;
  } else {
    maior = i;
  }
  if (dir < n && A[dir] > A[maior]) {
    maior = dir;
  }
  if (maior != i) {
    float temp = A[i];
    A[i] = A[maior];
    A[maior] = temp;
    MaxHeapify(A, maior, n);
  }
}

void BuildMaxHeap(float *A, int n) {
  int i;
  for(i = n / 2 - 1; i >= 0; i--) {
    MaxHeapify(A, i, n);
  }
}

void HeapSort(float *A, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    MaxHeapify(A, i, n);
  }
  for (int i = n - 1; i >= 1; i--) {
    float temp = A[0];
    A[0] = A[i];
    A[i] = temp;
    MaxHeapify(A, 0, i);
  }
}

// ------------------------------------------- QUICKSORT -------------------------------------------
int Particao(float *A, int p, int r) {
  float x = A[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (A[j] >= x) { // Troca ordem para maior valor na frente
      i++;
      float temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  float temp = A[i + 1];
  A[i + 1] = A[r];
  A[r] = temp;
  return i + 1;
}


void Quicksort(float *A, int p, int r) {
  if (p < r) {
    int q = Particao(A, p, r);
    Quicksort(A, p, q - 1);
    Quicksort(A, q + 1, r);
  }
}

// ------------------------------------------- BUBBLESORT -------------------------------------------

void Bubblesort(float A[], int n) {
  float x;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (A[j] < A[j + 1]) { // Troca ordem para maior valor na frente
        x = A[j];
        A[j] = A[j + 1];
        A[j + 1] = x;
      }
    }
  }
}

// ------------------------------------------- MERGESORT -------------------------------------------

void Merge(float *A, int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;
  float L[n1], R[n2];
  for (int i = 0; i < n1; i++) L[i] = A[l + i];
  for (int j = 0; j < n2; j++) R[j] = A[m + 1 + j];
  
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (L[i] >= R[j]) { // Troca ordem
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    A[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    A[k] = R[j];
    j++;
    k++;
  }
}

void MergeSort(float *A, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    MergeSort(A, l, m);
    MergeSort(A, m + 1, r);
    Merge(A, l, m, r);
  }
}

void aplicarOrdenacao(TCidade cidades[], int opcao, TArvore *arvore){
    for(int i = 0; i < 7; i++){
      switch(opcao){
        case 1:
          Selecao(cidades[i].nota, 3);
          break;
        case 2:
          Insercao(cidades[i].nota, 3);
          break;
        case 3:
          Shellsort(cidades[i].nota, 3);
          break;
        case 4:
          HeapSort(cidades[i].nota, 3);
          break;
        case 5:
          Quicksort(cidades[i].nota, 0, 2);
          break;
        case 6:
          Bubblesort(cidades[i].nota, 3);
          break;
        case 7:
          MergeSort(cidades[i].nota, 0, 2);
          break;
        default:
          printf("Opcao Invalida!");
          return;
          break;
      }
    }

    arvore->raiz = NULL;
    for(int i = 0; i < 5; i++){
        Inserir(&arvore->raiz, NULL, cidades[i]);
    } //Os elementos precisam ser reinseridos mas dessa vez na ordem correta
  
    printf("Notas das cidades ordenadas!");
  }

void aplicarOrdenacaoOpcao2(TCidade cidades[], int opcao, TArvore *arvore){

    // Para cada cidade, escolhe o método de ordenação
    for (int i = 0; i < 7; i++) {
        printf("\nEscolha um método de ordenação para as notas da cidade %s:\n", cidades[i].nome);
        menuOrdenacoes();
        scanf("%d", &opcao);

        // Aplica o método de ordenação escolhido para a cidade
        switch(opcao) {
            case 1:
                Selecao(cidades[i].nota, 3);
                break;
            case 2:
                Insercao(cidades[i].nota, 3);
                break;
            case 3:
                Shellsort(cidades[i].nota, 3);
                break;
            case 4:
                HeapSort(cidades[i].nota, 3);
                break;
            case 5:
                Quicksort(cidades[i].nota, 0, 2);
                break;
            case 6:
                Bubblesort(cidades[i].nota, 3);
                break;
            case 7:
                MergeSort(cidades[i].nota, 0, 2);
                break;
            default:
                printf("Método de ordenação inválido!\n");
                break;
        }

        // Após ordenar as notas da cidade, reinseri-la na árvore igual aplicarOrdenacao
        arvore->raiz = NULL;
        for (int j = 0; j < 7; j++) {
            Inserir(&arvore->raiz, NULL, cidades[j]);
        }

        printf("\nNotas da cidade %s ordenadas!\n", cidades[i].nome);
    }

    printf("\nÁrvore de cidades atualizada com as novas notas ordenadas!\n");
}


// ------------------------------------------------------------------------------------------------

int main(){

    srand(time(NULL)); //Faz com que os valores randomizados das notas não sejam sempre os mesmos
    gerarNotas();

    TArvore arvore;
    arvore.raiz = NULL;
    TCidade PesquisarCidade;
    char PesquisarNome[25];

    // Inserindo as cidades pré-definidas automaticamente na árvore
    for(int i = 0; i < 5; i++){
        Inserir(&arvore.raiz, NULL, cidades[i]);
    }

    int opcao;

    printf("\n\n\n\n--------------------Bem vindo ao nosso roteiro de viagem inteligente!--------------------\n\n");
    printf("Primeiro, vamos escolher como vamos ordenar as notas dos eventos para cada cidade! Escolha entre:\n");
    printf("1 - Usar apenas um metodo de ordenacao para as cidades\n");
    printf("2 - Usar um metodo de ordenacao para cada cidade\n");

    scanf("%d", &opcao);

    if(opcao == 1){
      menuOrdenacoes();
      scanf("%d", &opcao);
      aplicarOrdenacao(cidades, opcao, &arvore);
    } else if(opcao == 2){
        menuOrdenacoes();
        scanf("%d", &opcao);
        aplicarOrdenacaoOpcao2(cidades, opcao, &arvore);
    }




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
