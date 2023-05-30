#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* vetor;
    int quantidadeElementos;
} LISTA;

LISTA* criarLista(int tamanho) {
    LISTA* novaLista = (LISTA*) malloc(sizeof(LISTA));
    novaLista->vetor = (int*) malloc(tamanho * sizeof(int));
    novaLista->quantidadeElementos = 0;
    return novaLista;
}

void liberarLista(LISTA* lista) {
    free(lista->vetor);
    free(lista);
}

void inserirElemento(LISTA* lista, int elemento) {
    lista->vetor[lista->quantidadeElementos] = elemento;
    lista->quantidadeElementos++;
}

void inserirElementoOrdenado(LISTA* lista, int elemento) {
    int i, j;
    for (i = 0; i < lista->quantidadeElementos; i++) {
        if (elemento < lista->vetor[i]) {
            break;
        }
    }
    for (j = lista->quantidadeElementos; j > i; j--) {
        lista->vetor[j] = lista->vetor[j - 1];
    }
    lista->vetor[i] = elemento;
    lista->quantidadeElementos++;
}

void imprimirLista(LISTA* lista) {
    int i;
    for (i = 0; i < lista->quantidadeElementos; i++) {
        printf("%d ", lista->vetor[i]);
    }
    printf("\n");
}

int buscarSequencial(LISTA* lista, int elemento) {
    int i;
    for (i = 0; i < lista->quantidadeElementos; i++) {
        if (lista->vetor[i] == elemento) {
            return i;
        }
    }
    return -1;
}

int buscarSequencialOrdenada(LISTA* lista, int elemento) {
    int i;
    for (i = 0; i < lista->quantidadeElementos; i++) {
        if (lista->vetor[i] == elemento) {
            return i;
        } else if (lista->vetor[i] > elemento) {
            return -1;
        }
    }
    return -1;
}

int buscarBinariaIterativa(LISTA* lista, int elemento) {
    int inicio = 0;
    int fim = lista->quantidadeElementos - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (lista->vetor[meio] == elemento) {
            return meio;
        } else if (lista->vetor[meio] < elemento) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

int buscarBinariaRecursiva(LISTA* lista, int elemento, int inicio, int fim) {
    if (inicio > fim) {
        return -1;
    }

    int meio = (inicio + fim) / 2;
    if (lista->vetor[meio] == elemento) {
        return meio;
    } else if (lista->vetor[meio] < elemento) {
        return buscarBinariaRecursiva(lista, elemento, meio + 1, fim);
    } else {
        return buscarBinariaRecursiva(lista, elemento, inicio, meio - 1);
    }
}

int buscarMaiorElementoIterativo(LISTA* lista) {
    int i;
    int maior = lista->vetor[0];
    for (i = 1; i < lista->quantidadeElementos; i++) {
        if (lista->vetor[i] > maior) {
            maior = lista->vetor[i];
        }
    }
    return maior;
}

int buscarMaiorElementoRecursivo(LISTA* lista, int inicio, int fim) {
    if (inicio == fim) {
        return lista->vetor[inicio];
    } else {
        int meio = (inicio + fim) / 2;
        int maiorEsquerda = buscarMaiorElementoRecursivo(lista, inicio, meio);
        int maiorDireita = buscarMaiorElementoRecursivo(lista, meio + 1, fim);
        return maiorEsquerda > maiorDireita ? maiorEsquerda : maiorDireita;
    }
}

int buscarMenorElementoIterativo(LISTA* lista) {
    int i;
    int menor = lista->vetor[0];
    for (i = 1; i < lista->quantidadeElementos; i++) {
        if (lista->vetor[i] < menor) {
            menor = lista->vetor[i];
        }
    }
    return menor;
}

int buscarMenorElementoRecursivo(LISTA* lista, int inicio, int fim) {
    if (inicio == fim) {
        return lista->vetor[inicio];
    } else {
        int meio = (inicio + fim) / 2;
        int menorEsquerda = buscarMenorElementoRecursivo(lista, inicio, meio);
        int menorDireita = buscarMenorElementoRecursivo(lista, meio + 1, fim);
        return menorEsquerda < menorDireita ? menorEsquerda : menorDireita;
    }
}

int somarElementosIterativo(LISTA* lista) {
    int i;
    int soma = 0;
    for (i = 0; i < lista->quantidadeElementos; i++) {
        soma += lista->vetor[i];
    }
    return soma;
}

int somarElementosRecursivo(LISTA* lista, int indice) {
    if (indice == lista->quantidadeElementos) {
        return 0;
    } else {
        return lista->vetor[indice] + somarElementosRecursivo(lista, indice + 1);
    }
}

int multiplicarElementosIterativo(LISTA* lista) {
    int i;
    int produto = 1;
    for (i = 0; i < lista->quantidadeElementos; i++) {
        produto *= lista->vetor[i];
    }
    return produto;
}

int multiplicarElementosRecursivo(LISTA* lista, int indice) {
    if (indice == lista->quantidadeElementos) {
        return 1;
    } else {
        return lista->vetor[indice] * multiplicarElementosRecursivo(lista, indice + 1);
    }
}

int main() {
    LISTA* lista = criarLista(10);

    inserirElemento(lista, 5);
    inserirElemento(lista, 2);
    inserirElemento(lista, 9);
    inserirElemento(lista, 7);
    inserirElemento(lista, 1);

    printf("Elementos da lista: ");
    imprimirLista(lista);

    int elementoBusca;
    printf("Digite um número para buscar na lista: ");
    scanf("%d", &elementoBusca);
    int posicaoBusca = buscarSequencial(lista, elementoBusca);
    if (posicaoBusca != -1) {
        printf("Elemento %d encontrado na posição %d.\n", elementoBusca, posicaoBusca);
    } else {
        printf("Elemento %d não encontrado na lista.\n", elementoBusca);
    }

    LISTA* segundaLista = criarLista(30);
    int i;
    for (i = 0; i < 30; i++) {
        inserirElementoOrdenado(segundaLista, i + 1);
    }

    printf("Elementos da segunda lista: ");
    imprimirLista(segundaLista);

    printf("Digite um número para buscar na segunda lista: ");
    scanf("%d", &elementoBusca);
    posicaoBusca = buscarSequencial(segundaLista, elementoBusca);
    if (posicaoBusca != -1) {
        printf("Elemento %d encontrado na posição %d (Busca Sequencial).\n", elementoBusca, posicaoBusca);
    } else {
        printf("Elemento %d não encontrado na lista (Busca Sequencial).\n", elementoBusca);
    }

    posicaoBusca = buscarSequencialOrdenada(segundaLista, elementoBusca);
    if (posicaoBusca != -1) {
        printf("Elemento %d encontrado na posição %d (Busca Sequencial Ordenada).\n", elementoBusca, posicaoBusca);
    } else {
        printf("Elemento %d não encontrado na lista (Busca Sequencial Ordenada).\n", elementoBusca);
    }

    posicaoBusca = buscarBinariaIterativa(segundaLista, elementoBusca);
    if (posicaoBusca != -1) {
        printf("Elemento %d encontrado na posição %d (Busca Binária Iterativa).\n", elementoBusca, posicaoBusca);
    } else {
        printf("Elemento %d não encontrado na lista (Busca Binária Iterativa).\n", elementoBusca);
    }

    posicaoBusca = buscarBinariaRecursiva(segundaLista, elementoBusca, 0, segundaLista->quantidadeElementos - 1);
    if (posicaoBusca != -1) {
        printf("Elemento %d encontrado na posição %d (Busca Binária Recursiva).\n", elementoBusca, posicaoBusca);
    } else {
        printf("Elemento %d não encontrado na lista (Busca Binária Recursiva).\n", elementoBusca);
    }

    int maiorIterativo = buscarMaiorElementoIterativo(lista);
    printf("Maior elemento da primeira lista (Iterativo): %d\n", maiorIterativo);

    int maiorRecursivo = buscarMaiorElementoRecursivo(lista, 0, lista->quantidadeElementos - 1);
    printf("Maior elemento da primeira lista (Recursivo): %d\n", maiorRecursivo);

    int menorIterativo = buscarMenorElementoIterativo(lista);
    printf("Menor elemento da primeira lista (Iterativo): %d\n", menorIterativo);

    int menorRecursivo = buscarMenorElementoRecursivo(lista, 0, lista->quantidadeElementos - 1);
    printf("Menor elemento da primeira lista (Recursivo): %d\n", menorRecursivo);

    int somaIterativa = somarElementosIterativo(lista);
    printf("Soma dos elementos da primeira lista (Iterativo): %d\n", somaIterativa);

    int somaRecursiva = somarElementosRecursivo(lista, 0);
    printf("Soma dos elementos da primeira lista (Recursivo): %d\n", somaRecursiva);

    int produtoIterativo = multiplicarElementosIterativo(lista);
    printf("Produto dos elementos da primeira lista (Iterativo): %d\n", produtoIterativo);

    int produtoRecursivo = multiplicarElementosRecursivo(lista, 0);
    printf("Produto dos elementos da primeira lista (Recursivo): %d\n", produtoRecursivo);

    liberarLista(lista);
    liberarLista(segundaLista);

    return 0;
}
