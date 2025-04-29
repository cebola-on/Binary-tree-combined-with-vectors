#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_NOMES 10

// Estrutura da pessoa
typedef struct Pessoa {
    char nome[MAX_NOME];
    char cabelo[10];
    char olho[10];
    char pele[10];
} Pessoa;

// Estruturas da árvore
typedef struct NoFolha {
    char nomes[MAX_NOMES][MAX_NOME];
    int qtd;
} NoFolha;

typedef struct NoPele {
    char pele[10];
    NoFolha* folha;
    struct NoPele* prox;
} NoPele;

typedef struct NoOlho {
    char olho[10];
    NoPele* listaPele;
    struct NoOlho* prox;
} NoOlho;

typedef struct NoCabelo {
    char cabelo[10];
    NoOlho* listaOlho;
    struct NoCabelo* prox;
} NoCabelo;

typedef struct ArvoreCaracteristicas {
    NoCabelo* listaCabelo;
} ArvoreCaracteristicas;

const char* opCabelos[] = {"Preto", "Ruivo", "Loiro"};
const char* opOlhos[] = {"Castanho", "Verde", "Azul"};
const char* opPeles[] = {"Branco", "Preto", "Castanho"};

// Protótipos das funções
ArvoreCaracteristicas* criarArvore();
void inserirPessoasFixas(ArvoreCaracteristicas* arv);
void inserirPessoaNaArvore(ArvoreCaracteristicas* arv, Pessoa p);
void listarPorCaracteristicas(ArvoreCaracteristicas* arv, int ordem);

// Implementações
ArvoreCaracteristicas* criarArvore() {
    ArvoreCaracteristicas* arv = (ArvoreCaracteristicas*)malloc(sizeof(ArvoreCaracteristicas));
    arv->listaCabelo = NULL;
    return arv;
}

NoFolha* criarFolha() {
    NoFolha* folha = (NoFolha*)malloc(sizeof(NoFolha));
    folha->qtd = 0;
    return folha;
}

void inserirPessoaNaArvore(ArvoreCaracteristicas* arv, Pessoa p) {
    NoCabelo *nc = arv->listaCabelo, *prevC = NULL;
    while (nc && strcmp(nc->cabelo, p.cabelo) != 0) {
        prevC = nc;
        nc = nc->prox;
    }
    if (!nc) {
        nc = (NoCabelo*)malloc(sizeof(NoCabelo));
        strcpy(nc->cabelo, p.cabelo);
        nc->listaOlho = NULL;
        nc->prox = NULL;
        if (prevC) prevC->prox = nc;
        else arv->listaCabelo = nc;
    }

    NoOlho *no = nc->listaOlho, *prevO = NULL;
    while (no && strcmp(no->olho, p.olho) != 0) {
        prevO = no;
        no = no->prox;
    }
    if (!no) {
        no = (NoOlho*)malloc(sizeof(NoOlho));
        strcpy(no->olho, p.olho);
        no->listaPele = NULL;
        no->prox = NULL;
        if (prevO) prevO->prox = no;
        else nc->listaOlho = no;
    }

    NoPele *np = no->listaPele, *prevP = NULL;
    while (np && strcmp(np->pele, p.pele) != 0) {
        prevP = np;
        np = np->prox;
    }
    if (!np) {
        np = (NoPele*)malloc(sizeof(NoPele));
        strcpy(np->pele, p.pele);
        np->folha = criarFolha();
        np->prox = NULL;
        if (prevP) prevP->prox = np;
        else no->listaPele = np;
    }

    if (np->folha->qtd < MAX_NOMES) {
        strcpy(np->folha->nomes[np->folha->qtd], p.nome);
        np->folha->qtd++;
    } else {
        printf("Folha cheia!\n");
    }
}

int comparar(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

void listarPorCaracteristicas(ArvoreCaracteristicas* arv, int ordem) {
    Pessoa temp;
    printf("Para listar, insira novamente as características:\n");
    int ic, io, ip;
    printf("Selecione a cor do cabelo:\n1 - Preto\n2 - Ruivo\n3 - Loiro\nOpcao: ");
    scanf("%d", &ic);
    strcpy(temp.cabelo, opCabelos[ic - 1]);

    printf("Selecione a cor dos olhos:\n1 - Castanho\n2 - Verde\n3 - Azul\nOpcao: ");
    scanf("%d", &io);
    strcpy(temp.olho, opOlhos[io - 1]);

    printf("Selecione a cor da pele:\n1 - Branco\n2 - Preto\n3 - Castanho\nOpcao: ");
    scanf("%d", &ip);
    strcpy(temp.pele, opPeles[ip - 1]);

    NoCabelo* nc = arv->listaCabelo;
    while (nc && strcmp(nc->cabelo, temp.cabelo) != 0) nc = nc->prox;
    if (!nc) return;

    NoOlho* no = nc->listaOlho;
    while (no && strcmp(no->olho, temp.olho) != 0) no = no->prox;
    if (!no) return;

    NoPele* np = no->listaPele;
    while (np && strcmp(np->pele, temp.pele) != 0) np = np->prox;
    if (!np) return;

    if (ordem) {
        char* nomesOrdenados[MAX_NOMES];
        for (int i = 0; i < np->folha->qtd; i++) {
            nomesOrdenados[i] = np->folha->nomes[i];
        }
        qsort(nomesOrdenados, np->folha->qtd, sizeof(char*), comparar);
        for (int i = 0; i < np->folha->qtd; i++) {
            printf("%s\n", nomesOrdenados[i]);
        }
    } else {
        for (int i = 0; i < np->folha->qtd; i++) {
            printf("%s\n", np->folha->nomes[i]);
        }
    }
}

void inserirPessoasFixas(ArvoreCaracteristicas* arv) {
    Pessoa pessoas[] = {
        {"Ana", "Preto", "Castanho", "Branco"},
        {"Bruno", "Loiro", "Azul", "Branco"},
        {"Carla", "Castanho", "Verde", "Castanho"},
        {"Daniel", "Preto", "Azul", "Preto"},
        {"Elisa", "Loiro", "Verde", "Branco"},
        {"Felipe", "Castanho", "Castanho", "Castanho"},
        {"Gabriela", "Preto", "Verde", "Branco"},
        {"Henrique", "Loiro", "Azul", "Castanho"},
        {"Isabela", "Castanho", "Castanho", "Preto"},
        {"João", "Preto", "Azul", "Branco"},
        {"Karina", "Loiro", "Verde", "Branco"},
        {"Lucas", "Castanho", "Castanho", "Castanho"},
        {"Mariana", "Preto", "Verde", "Preto"},
        {"Natan", "Loiro", "Azul", "Branco"},
        {"Olívia", "Castanho", "Castanho", "Castanho"},
        {"Pedro", "Preto", "Verde", "Castanho"},
        {"Queila", "Loiro", "Azul", "Branco"},
        {"Rafael", "Castanho", "Verde", "Preto"},
        {"Sabrina", "Preto", "Azul", "Branco"},
        {"Thiago", "Loiro", "Verde", "Castanho"},
        {"Ursula", "Castanho", "Castanho", "Branco"},
        {"Victor", "Preto", "Verde", "Preto"},
        {"Wanda", "Loiro", "Azul", "Castanho"},
        {"Xande", "Castanho", "Verde", "Branco"},
        {"Yasmin", "Preto", "Castanho", "Preto"},
        {"Zeca", "Loiro", "Verde", "Branco"},
        {"Amanda", "Castanho", "Castanho", "Castanho"},
        {"Breno", "Preto", "Azul", "Castanho"},
        {"Camila", "Loiro", "Verde", "Preto"},
        {"Diego", "Castanho", "Verde", "Branco"},
        {"Eduarda", "Preto", "Castanho", "Castanho"},
        {"Fábio", "Loiro", "Azul", "Branco"},
        {"Giovana", "Castanho", "Verde", "Castanho"},
        {"Heitor", "Preto", "Azul", "Preto"},
        {"Ivana", "Loiro", "Castanho", "Branco"},
        {"Jorge", "Castanho", "Verde", "Preto"},
        {"Kelly", "Preto", "Azul", "Castanho"},
        {"Leandro", "Loiro", "Verde", "Branco"},
        {"Mirela", "Castanho", "Castanho", "Castanho"},
        {"Nilo", "Preto", "Verde", "Branco"},
        {"Orlanda", "Loiro", "Azul", "Castanho"},
        {"Paulo", "Castanho", "Verde", "Preto"},
        {"Quésia", "Preto", "Castanho", "Branco"},
        {"Rodrigo", "Loiro", "Verde", "Castanho"},
        {"Sílvia", "Castanho", "Azul", "Preto"},
        {"Túlio", "Preto", "Verde", "Castanho"},
        {"Valéria", "Loiro", "Castanho", "Branco"},
        {"William", "Castanho", "Verde", "Preto"},
        {"Ximena", "Preto", "Azul", "Branco"},
        {"Ygor", "Loiro", "Verde", "Castanho"}
    };

    int n = sizeof(pessoas) / sizeof(Pessoa);
    for (int i = 0; i < n; i++) {
        inserirPessoaNaArvore(arv, pessoas[i]);
    }
}

void buscarPorNome(ArvoreCaracteristicas* arv, const char* nomeBusca) {
    NoCabelo* nc = arv->listaCabelo;
    while (nc) {
        NoOlho* no = nc->listaOlho;
        while (no) {
            NoPele* np = no->listaPele;
            while (np) {
                for (int i = 0; i < np->folha->qtd; i++) {
                    if (strcmp(np->folha->nomes[i], nomeBusca) == 0) {
                        printf("\nNome encontrado: %s\nCabelo: %s\nOlho: %s\nPele: %s\n",
                            nomeBusca, nc->cabelo, no->olho, np->pele);
                        return;
                    }
                }
                np = np->prox;
            }
            no = no->prox;
        }
        nc = nc->prox;
    }
    printf("Nome nao encontrado.\n");
}

void menu(ArvoreCaracteristicas* arv) {
    int op;
    do {
        printf("\n1 - Inserir nova pessoa\n2 - Listar por caracteristicas\n3 - Buscar por nome\n4 - Sair\nEscolha: ");
        scanf("%d", &op);

        if (op == 1) {
            Pessoa nova;
            int ic, io, ip;
            printf("Selecione a cor do cabelo:\n1 - Preto\n2 - Ruivo\n3 - Loiro\nOpcao: ");
            scanf("%d", &ic);
            strcpy(nova.cabelo, opCabelos[ic - 1]);

            printf("Selecione a cor dos olhos:\n1 - Castanho\n2 - Verde\n3 - Azul\nOpcao: ");
            scanf("%d", &io);
            strcpy(nova.olho, opOlhos[io - 1]);

            printf("Selecione a cor da pele:\n1 - Branco\n2 - Preto\n3 - Castanho\nOpcao: ");
            scanf("%d", &ip);
            strcpy(nova.pele, opPeles[ip - 1]);

            printf("Digite o nome: ");
            scanf("%s", nova.nome);

            inserirPessoaNaArvore(arv, nova);

        } else if (op == 2) {
            int ord;
            printf("Deseja ordenar os nomes em ordem alfabética? (1-sim / 0-nao): ");
            scanf("%d", &ord);
            listarPorCaracteristicas(arv, ord);

        } else if (op == 3) {
            char nomeBusca[MAX_NOME];
            printf("Digite o nome a ser buscado: ");
            scanf("%s", nomeBusca);
            buscarPorNome(arv, nomeBusca);
        }
    } while (op != 4);
}

int main() {
    ArvoreCaracteristicas* arv = criarArvore();
    inserirPessoasFixas(arv);
    menu(arv);
    return 0;
}
