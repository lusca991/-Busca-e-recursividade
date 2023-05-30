#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    int idade;
    float coeficiente;
} ALUNO;

typedef struct {
    ALUNO* alunos;
    int quantidadeAlunos;
} TURMA;

TURMA* criarTurma(int quantidadeAlunos) {
    TURMA* turma = (TURMA*)malloc(sizeof(TURMA));
    turma->alunos = (ALUNO*)malloc(quantidadeAlunos * sizeof(ALUNO));
    turma->quantidadeAlunos = quantidadeAlunos;
    return turma;
}

void liberarTurma(TURMA* turma) {
    free(turma->alunos);
    free(turma);
}

void inserirAluno(TURMA* turma, int codigo, const char* nome, int idade, float coeficiente) {
    ALUNO aluno;
    aluno.codigo = codigo;
    strcpy(aluno.nome, nome);
    aluno.idade = idade;
    aluno.coeficiente = coeficiente;

    turma->alunos[turma->quantidadeAlunos] = aluno;
    turma->quantidadeAlunos++;
}

void buscarAlunoSequencial(TURMA* turma, int codigo) {
    int i;
    for (i = 0; i < turma->quantidadeAlunos; i++) {
        if (turma->alunos[i].codigo == codigo) {
            printf("Aluno encontrado:\n");
            printf("Código: %d\n", turma->alunos[i].codigo);
            printf("Nome: %s\n", turma->alunos[i].nome);
            printf("Idade: %d\n", turma->alunos[i].idade);
            printf("Coeficiente: %.2f\n", turma->alunos[i].coeficiente);
            return;
        }
    }
    printf("Aluno não encontrado.\n");
}

int compararAlunos(const void* a, const void* b) {
    ALUNO* alunoA = (ALUNO*)a;
    ALUNO* alunoB = (ALUNO*)b;
    return alunoA->codigo - alunoB->codigo;
}

void buscarAlunoBinariaRecursiva(ALUNO* alunos, int codigo, int inicio, int fim) {
    if (inicio > fim) {
        printf("Aluno não encontrado.\n");
        return;
    }

    int meio = (inicio + fim) / 2;

    if (alunos[meio].codigo == codigo) {
        printf("Aluno encontrado:\n");
        printf("Código: %d\n", alunos[meio].codigo);
        printf("Nome: %s\n", alunos[meio].nome);
        printf("Idade: %d\n", alunos[meio].idade);
        printf("Coeficiente: %.2f\n", alunos[meio].coeficiente);
    } else if (alunos[meio].codigo < codigo) {
        buscarAlunoBinariaRecursiva(alunos, codigo, meio + 1, fim);
    } else {
        buscarAlunoBinariaRecursiva(alunos, codigo, inicio, meio - 1);
    }
}

void imprimirCodigoNomeAlunos(TURMA* turma) {
    int i;
    for (i = 0; i < turma->quantidadeAlunos; i++) {
        printf("Código: %d, Nome: %s\n", turma->alunos[i].codigo, turma->alunos[i].nome);
    }
}

int main() {
    TURMA* turma = criarTurma(5);

    inserirAluno(turma, 1, "Aluno 1", 20, 7.5);
    inserirAluno(turma, 2, "Aluno 2", 21, 8.2);
    inserirAluno(turma, 3, "Aluno 3", 22, 7.8);
    inserirAluno(turma, 4, "Aluno 4", 19, 6.9);
    inserirAluno(turma, 5, "Aluno 5", 20, 9.1);

    printf("Código e nome dos alunos:\n");
    imprimirCodigoNomeAlunos(turma);

    int codigoBusca;
    printf("Digite o código do aluno a ser buscado: ");
    scanf("%d", &codigoBusca);
    buscarAlunoSequencial(turma, codigoBusca);

    qsort(turma->alunos, turma->quantidadeAlunos, sizeof(ALUNO), compararAlunos);

    printf("Código e nome dos alunos (ordenados):\n");
    imprimirCodigoNomeAlunos(turma);

    printf("Digite o código do aluno a ser buscado (busca binária recursiva): ");
    scanf("%d", &codigoBusca);
    buscarAlunoBinariaRecursiva(turma->alunos, codigoBusca, 0, turma->quantidadeAlunos - 1);

    liberarTurma(turma);

    return 0;
}
