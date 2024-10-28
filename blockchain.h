#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definindo o tamanho do hash
#define HASH_SIZE 64

// Estrutura para representar um bloco na blockchain
typedef struct Block {
    int index;               // Índice do bloco na blockchain
    time_t timestamp;        // Data e hora da criação do bloco
    char previous_hash[HASH_SIZE];  // Hash do bloco anterior
    char hash[HASH_SIZE];           // Hash deste bloco
    char data[256];          // Dados armazenados no bloco
    struct Block* next;      // Ponteiro para o próximo bloco
} Block;

// Estrutura para representar a blockchain
typedef struct Blockchain {
    Block* head;             // Ponteiro para o bloco gênesis (inicial)
} Blockchain;

// Funções principais para manipulação da blockchain
Blockchain* create_blockchain();                         // Cria uma nova blockchain
Block* create_block(int index, const char* previous_hash, const char* data);  // Cria um novo bloco
void add_block(Blockchain* blockchain, Block* new_block); // Adiciona um bloco à blockchain
void print_block(Block* block);                          // Imprime informações de um bloco
void print_blockchain(Blockchain* blockchain);           // Imprime toda a blockchain
void calculate_hash(Block* block);                       // Calcula o hash do bloco
void free_blockchain(Blockchain* blockchain);            // Libera a memória da blockchain

#endif
