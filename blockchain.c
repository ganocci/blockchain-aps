#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 64

// Estrutura básica de um bloco
typedef struct Block {
    int stepId;                    // ID da etapa (1: Coleta, 2: Processamento, etc.)
    char previousHash[HASH_SIZE];   // Hash do bloco anterior
    char hash[HASH_SIZE];           // Hash do bloco atual
    char data[512];                 // Informações sobre a etapa
    time_t timestamp;               // Timestamp da transação
    struct Block* next;             // Ponteiro para o próximo bloco
} Block;

// Função para gerar hash simples
unsigned long simpleHash(const char* input) {
    unsigned long hash = 5381;  // Um valor inicial, pode ser qualquer número
    int c;

    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

// Função para gerar hash usando a função simples
void generateHash(Block* block) {
    char input[1024];  // String para concatenar todos os dados a serem hashados
    snprintf(input, sizeof(input), "%ld%d%s%s", block->timestamp, block->stepId, block->previousHash, block->data);
    
    // Calcula o hash simples
    unsigned long hashValue = simpleHash(input);
    
    // Converte o hash para string hexadecimal
    snprintf(block->hash, HASH_SIZE, "%lx", hashValue);
}

Block* createBlock(int stepId, const char* previousHash, const char* data) {
    Block* newBlock = (Block*)malloc(sizeof(Block));

    newBlock->stepId = stepId;

    // Copiar o hash do bloco anterior
    strcpy(newBlock->previousHash, previousHash);

    // Copiar os dados
    strcpy(newBlock->data, data);

    // Definir o timestamp
    newBlock->timestamp = time(NULL);

    // Gerar o hash do bloco
    generateHash(newBlock);

    newBlock->next = NULL;  // O próximo bloco ainda não existe

    return newBlock;
}

Block* addBlock(Block *lastBlock, char* data) {
    // Cria um novo bloco, passando o ID da etapa e o hash do bloco anterior
    Block *newBlock = createBlock(lastBlock->stepId + 1, lastBlock->hash, data);

    // Conecta o novo bloco ao anterior
    lastBlock->next = newBlock;

    return newBlock;
}

Block* createGenesisBlock() {
    return createBlock(0, "0", "Genesis Block - Coleta inicial dos dispositivos eletrônicos");
}

void printBlock(Block* block) {
    char buffer[26];
    struct tm* tm_info;

    tm_info = localtime(&(block->timestamp));
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    printf("========================================\n");
    printf("Etapa: %d\n", block->stepId);
    printf("Dados: %s\n", block->data);
    printf("Hash Atual (Etapa %d): %s\n", block->stepId, block->hash);
    printf("Hash Anterior (Etapa %d): %s\n", block->stepId - 1, block->previousHash);
    printf("Timestamp: %s\n", buffer);
    printf("========================================\n\n");
}
void printBlockchain(Block *blockchain) {
    Block *currentBlock = blockchain;
    while (currentBlock != NULL) {
        printBlock(currentBlock);  // Chama a função que imprime cada bloco formatado
        currentBlock = currentBlock->next;
    }
}

int main() {
    Block *blockchain = createGenesisBlock();
    
    Block *lastBlock = blockchain;
    lastBlock = addBlock(lastBlock, "Triagem e categorização dos componentes");
    lastBlock = addBlock(lastBlock, "Desmontagem manual dos equipamentos eletrônicos");
    lastBlock = addBlock(lastBlock, "Trituração e fragmentação dos materiais eletrônicos");
    lastBlock = addBlock(lastBlock, "Separação especializada dos materiais recicláveis");
    lastBlock = addBlock(lastBlock, "Reutilização e redistribuição de componentes reciclados");

    printBlockchain(blockchain);

    return 0;
}
