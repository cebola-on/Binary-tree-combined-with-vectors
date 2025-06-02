------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Explanation of the Characteristic Tree Code
This document provides a detailed overview of a C program that implements a multi-level tree data structure to organize and query people based on three attributes: hair color, eye color, and skin color. The tree is built with nodes for each attribute and leaf nodes that store names of people sharing those exact combinations of attributes.

1. Data Structures
1.1. Pessoa (Person)
typedef struct Pessoa {
    char nome[MAX_NOME];
    char cabelo[10];
    char olho[10];
    char pele[10];
} Pessoa;

Represents an individual with a name and three attributes: hair color, eye color, and skin color.
1.2. NoFolha (Leaf Node)
typedef struct NoFolha {
    char nomes[MAX_NOMES][MAX_NOME];
    int qtd;
} NoFolha;

A leaf of the tree that can store up to MAX_NOMES names of people sharing the same attribute combination. The field qtd tracks how many names are stored.
1.3. NoPele, NoOlho, and NoCabelo (Skin, Eye, and Hair Nodes)
// Skin node, points to its leaf of names
typedef struct NoPele {
    char pele[10];
    NoFolha* folha;
    struct NoPele* prox;
} NoPele;

// Eye node, linked list of NoPele
typedef struct NoOlho {
    char olho[10];
    NoPele* listaPele;
    struct NoOlho* prox;
} NoOlho;

// Hair node, linked list of NoOlho
typedef struct NoCabelo {
    char cabelo[10];
    NoOlho* listaOlho;
    struct NoCabelo* prox;
} NoCabelo;

Each attribute node contains:
A string holding the attribute value (e.g., "Black").

A pointer to the next level’s linked list (listaOlho or listaPele).

A pointer prox to the next node at the same level.

1.4. ArvoreCaracteristicas (Characteristic Tree)
typedef struct ArvoreCaracteristicas {
    NoCabelo* listaCabelo;
} ArvoreCaracteristicas;

The entry point of the structure, referencing a linked list of hair-color nodes.

2. Key Functions
2.1. criarArvore()
ArvoreCaracteristicas* criarArvore() {
    ArvoreCaracteristicas* arv = malloc(sizeof(*arv));
    arv->listaCabelo = NULL;
    return arv;
}

Allocates and initializes an empty characteristic tree with no hair-color nodes.
2.2. criarFolha()
NoFolha* criarFolha() {
    NoFolha* folha = malloc(sizeof(*folha));
    folha->qtd = 0;
    return folha;
}

Allocates a new leaf node and sets its count of stored names to zero.
2.3. inserirPessoaNaArvore(arv, p)
Inserts a Pessoa into the tree in three hierarchical steps:
Hair Level: Search for a NoCabelo matching p.cabelo; if not found, create and append it.

Eye Level: Within that hair node, search for a NoOlho matching p.olho; if absent, create and append.

Skin Level: Within that eye node, search for a NoPele matching p.pele; if absent, create it along with a new leaf.

Leaf Insertion: Add p.nome into the NoFolha if it has space, otherwise print "Folha cheia!".

2.4. comparar(a, b)
int comparar(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

Comparison function for qsort, sorts strings alphabetically.
2.5. listarPorCaracteristicas(arv, ordem)
Prompts the user to select indices for hair, eye, and skin colors.

Traverses the tree levels to locate the corresponding leaf.

If ordem == 1, copies names to an auxiliary array, sorts with qsort, and prints alphabetically.

If ordem == 0, prints names in insertion order.

2.6. inserirPessoasFixas(arv)
Populates the tree with a predefined array of ~50 Pessoa instances by repeatedly calling inserirPessoaNaArvore.
2.7. buscarPorNome(arv, nomeBusca)
Performs a full traversal of the three-level tree, examining each leaf’s names. On match, prints the person’s name and attributes; otherwise, prints "Name not found."
2.8. menu(arv)
Interactive loop offering:
Insert a new person

List by characteristics

Search by name

Exit

Each option invokes the respective function above.
2.9. main()
Program flow:
Create an empty tree via criarArvore().

Populate fixed entries with inserirPessoasFixas().

Enter user-driven menu with menu().


3. Execution Flow
Initialization: Allocate tree structure with no nodes.

Initial Population: Insert ~50 people covering varied attribute combinations.

User Interaction: Add new persons, list by attributes, or search by name.

Termination: Selecting option 4 ends the program.


4. Considerations and Limitations
Maximum Capacity: Each leaf can hold up to 10 names. Exceeding this limit prints "Folha cheia!".

Time Complexity: Linear search in linked lists at each level (hair → eye → skin) yields O(n) in the worst case.

Potential Enhancements:

Use balanced trees or hash tables at each level for faster search and insertion.

Implement memory deallocation for all nodes.

Allow dynamic resizing of leaf lists instead of a fixed-size array.


This English version provides a comprehensive mapping of each part of the original C code, enabling clear understanding, maintenance, and possible future improvements.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Explicação do Funcionamento do Código de Árvore de Características
Este documento tem como objetivo detalhar o funcionamento do programa em C que implementa uma estrutura de árvore para organizar e buscar pessoas com base em três características: cor do cabelo, cor dos olhos e cor da pele. A árvore é composta por nós correspondentes a cada característica e folhas que armazenam nomes de pessoas.

1. Estruturas de Dados
1.1. Pessoa
typedef struct Pessoa {
    char nome[MAX_NOME];
    char cabelo[10];
    char olho[10];
    char pele[10];
} Pessoa;

Representa uma pessoa e suas três características: nome, cor do cabelo, cor dos olhos e cor da pele.
1.2. NoFolha
typedef struct NoFolha {
    char nomes[MAX_NOMES][MAX_NOME];
    int qtd;
} NoFolha;

Folha da árvore que armazena até MAX_NOMES nomes de pessoas que compartilham as mesmas características definidas pelos nós-pais.
1.3. NoPele, NoOlho e NoCabelo
// Nó de pele, aponta para a folha de nomes
typedef struct NoPele {
    char pele[10];
    NoFolha* folha;
    struct NoPele* prox;
} NoPele;

// Nó de olho, lista encadeada de NoPele
typedef struct NoOlho {
    char olho[10];
    NoPele* listaPele;
    struct NoOlho* prox;
} NoOlho;

// Nó de cabelo, lista encadeada de NoOlho
typedef struct NoCabelo {
    char cabelo[10];
    NoOlho* listaOlho;
    struct NoCabelo* prox;
} NoCabelo;

Cada nó de nível (NoCabelo, NoOlho, NoPele) possui:
Uma string com o valor da característica (e.g., "Preto").

Um ponteiro para a lista de nós do próximo nível.

Um ponteiro para o próximo nó do mesmo nível (prox).

1.4. ArvoreCaracteristicas
typedef struct ArvoreCaracteristicas {
    NoCabelo* listaCabelo;
} ArvoreCaracteristicas;

Ponto de entrada da estrutura, que referencia a lista encadeada de nós de cabelo.

2. Funções Principais
2.1. criarArvore()
ArvoreCaracteristicas* criarArvore() {
    ArvoreCaracteristicas* arv = malloc(sizeof(*arv));
    arv->listaCabelo = NULL;
    return arv;
}

Aloca e inicializa a árvore com a lista de cabelos vazia.
2.2. criarFolha()
NoFolha* criarFolha() {
    NoFolha* folha = malloc(sizeof(*folha));
    folha->qtd = 0;
    return folha;
}

Aloca uma folha nova, com contagem de nomes iniciada em zero.
2.3. inserirPessoaNaArvore(arv, p)
Processo de três passos para inserir uma Pessoa:
Nível Cabelo: Busca nó com p.cabelo. Se não existir, cria um novo NoCabelo e o adiciona ao fim da lista.

Nível Olho: No nó de cabelo correspondente, busca NoOlho com p.olho. Se não existir, cria e adiciona.

Nível Pele: No nó de olho, busca NoPele com p.pele. Se não existir, cria, adiciona e inicializa sua NoFolha.

Inserção na Folha: Coloca p.nome na próxima posição disponível de NoFolha, se ainda não tiver atingido MAX_NOMES.

2.4. comparar(a, b)
Função de comparação utilizada pelo qsort para ordenar nomes em ordem alfabética.
2.5. listarPorCaracteristicas(arv, ordem)
Solicita ao usuário escolher índices para cabelo, olho e pele.

Percorre os níveis da árvore até encontrar a folha correspondente.

Se ordem == 1, copia nomes em vetor auxiliar, ordena via qsort e imprime em ordem alfabética.

Caso contrário, imprime na ordem de inserção.

2.6. inserirPessoasFixas(arv)
Insere um conjunto pré-definido de ~50 pessoas chamando inserirPessoaNaArvore para cada uma.
2.7. buscarPorNome(arv, nomeBusca)
Percorre toda a árvore (todos os níveis) verificando cada nome em cada NoFolha. Se encontrar, imprime características associadas.
2.8. menu(arv)
Loop interativo que apresenta opções:
Inserir nova pessoa

Listar por características

Buscar por nome

Sair

Cada opção chama as funções adequadas.
2.9. main()
Fluxo principal:
Cria árvore com criarArvore().

Popula com inserirPessoasFixas().

Inicia interface com menu().


3. Fluxo de Execução
Inicialização: Aloca árvores sem nós.

População Inicial: Adiciona ~50 pessoas com características variadas.

Interação: Usuário pode inserir novas pessoas, listar ou buscar.

Encerramento: Ao escolher a opção 4, o programa finaliza.


4. Considerações e Limitações
Capacidade máxima: Cada folha suporta até 10 nomes. Excesso gera mensagem "Folha cheia!".

Complexidade: Busca e inserção são lineares em cada nível (lista encadeada). Três níveis → O(n) em pior caso.

Melhorias:

Substituir listas encadeadas por árvores balanceadas para reduzir complexidade.

Implementar desalocação de memória.

Tornar dinâmico o tamanho das folhas.


Este documento fornece uma visão detalhada de cada parte do código, permitindo compreensão e futura manutenção ou aprimoramento da estrutura de dados implementada.
