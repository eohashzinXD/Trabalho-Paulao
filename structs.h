#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS_VEREADOR 500
#define MIN_CANDIDATOS_VEREADOR 100
#define MAX_CANDIDATOS_PREFEITO 50
#define MIN_CANDIDATOS_PREFEITO 10
#define MAX_ELEITORES 500
#define MIN_ELEITORES 300
#define MAX_NAME_LEN 100

typedef struct {
    char nome[MAX_NAME_LEN];
    int numero;
    int numero_partido;
    char sigla_partido[10];
} Vereador;

typedef struct {
    char nome[MAX_NAME_LEN];
    int numero;
    char sigla_partido[10];
} Prefeito;

typedef struct {
    char nome[MAX_NAME_LEN];
    int titulo;
    char deficiencia;
    char compareceu;
} Eleitor;

typedef struct {
    int voto_vereador;
    int voto_prefeito;
} Voto;