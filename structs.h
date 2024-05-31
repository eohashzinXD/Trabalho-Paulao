#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define constantes para o máximo e mínimo de candidatos e eleitores
#define MAX_CANDIDATOS_VEREADOR 500
#define MIN_CANDIDATOS_VEREADOR 100
#define MAX_CANDIDATOS_PREFEITO 50
#define MIN_CANDIDATOS_PREFEITO 10
#define MAX_ELEITORES 500
#define MIN_ELEITORES 300
#define MAX_NAME_LEN 100

// Estrutura para representar um Vereador
typedef struct {
    char nome[MAX_NAME_LEN];  // Nome do candidato a vereador
    int numero;               // Número do candidato a vereador
    int numero_partido;       // Número do partido do candidato a vereador
    char sigla_partido[10];   // Sigla do partido do candidato a vereador
} Vereador;

// Estrutura para representar um Prefeito
typedef struct {
    char nome[MAX_NAME_LEN];  // Nome do candidato a prefeito
    int numero;               // Número do candidato a prefeito
    char sigla_partido[10];   // Sigla do partido do candidato a prefeito
} Prefeito;

// Estrutura para representar um Eleitor
typedef struct {
    char nome[MAX_NAME_LEN];  // Nome do eleitor
    long int tituloDeEleitor; // Título de eleitor
    char deficiencia[2];      // Informação sobre deficiência (S/N)
    char compareceu[2];       // Informação sobre comparecimento (S/N)
} Eleitor;

// Estrutura para representar um Voto
typedef struct {
    int voto_vereador;        // Voto para vereador
    int voto_prefeito;        // Voto para prefeito
} Voto;