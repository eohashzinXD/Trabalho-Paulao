#include "structs.h"

int carregarCandidatosVereador(Vereador *candidatos, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de candidatos a vereador");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%99[^,],%d,%d,%9s\n", 
                  candidatos[count].nome, 
                  &candidatos[count].numero, 
                  &candidatos[count].numero_partido, 
                  candidatos[count].sigla_partido) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

int carregarCandidatosPrefeito(Prefeito *candidatos, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de candidatos a prefeito");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%99[^,],%d,%9s\n", 
                  candidatos[count].nome, 
                  &candidatos[count].numero, 
                  candidatos[count].sigla_partido) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

int carregarEleitores(Eleitor *eleitores, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de eleitores");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%99[^,],%d,%c,%c\n", 
                  eleitores[count].nome, 
                  &eleitores[count].titulo, 
                  &eleitores[count].deficiencia, 
                  &eleitores[count].compareceu) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

void votar(Eleitor *eleitores, int numEleitores, Vereador *vereadores, int numVereadores, Prefeito *prefeitos, int numPrefeitos) {
    FILE *votosFile = fopen("votos.bin", "wb");
    if (!votosFile) {
        perror("Erro ao abrir arquivo de votos");
        return;
    }

    for (int i = 0; i < numEleitores; i++) {
        if (eleitores[i].compareceu == 'N') {
            printf("Eleitor %s (%d) votando...\n", eleitores[i].nome, eleitores[i].titulo);
            int votoVereador, votoPrefeito;
            printf("Digite o número do candidato a vereador ou 0 para voto branco: ");
            scanf("%d", &votoVereador);
            printf("Digite o número do candidato a prefeito ou 0 para voto branco: ");
            scanf("%d", &votoPrefeito);

            Voto voto;
            voto.voto_vereador = votoVereador;
            voto.voto_prefeito = votoPrefeito;

            fwrite(&voto, sizeof(Voto), 1, votosFile);
            eleitores[i].compareceu = 'S';
        }
    }

    fclose(votosFile);
}

void apurar() {
    FILE *votosFile = fopen("votos.bin", "rb");
    if (!votosFile) {
        perror("Erro ao abrir arquivo de votos");
        return;
    }

    Voto voto;
    int totalVotosVereador[1000] = {0};
    int totalVotosPrefeito[100] = {0};

    while (fread(&voto, sizeof(Voto), 1, votosFile) == 1) {
        if (voto.voto_vereador >= 0 && voto.voto_vereador < 1000) {
            totalVotosVereador[voto.voto_vereador]++;
        }
        if (voto.voto_prefeito >= 0 && voto.voto_prefeito < 100) {
            totalVotosPrefeito[voto.voto_prefeito]++;
        }
    }

    fclose(votosFile);

    FILE *resultadoFile = fopen("resultado.txt", "w");
    if (!resultadoFile) {
        perror("Erro ao abrir arquivo de resultados");
        return;
    }

    fprintf(resultadoFile, "Resultados para Vereador:\n");
    for (int i = 0; i < 1000; i++) {
        if (totalVotosVereador[i] > 0) {
            fprintf(resultadoFile, "Número: %d, Votos: %d\n", i, totalVotosVereador[i]);
        }
    }

    fprintf(resultadoFile, "\nResultados para Prefeito:\n");
    for (int i = 0; i < 100; i++) {
        if (totalVotosPrefeito[i] > 0) {
            fprintf(resultadoFile, "Número: %d, Votos: %d\n", i, totalVotosPrefeito[i]);
        }
    }

    fclose(resultadoFile);
}

int main() {
    Vereador vereadores[MAX_CANDIDATOS_VEREADOR];
    Prefeito prefeitos[MAX_CANDIDATOS_PREFEITO];
    Eleitor eleitores[MAX_ELEITORES];

    int numVereadores = carregarCandidatosVereador(vereadores, "vereadores.txt");
    if (numVereadores < MIN_CANDIDATOS_VEREADOR || numVereadores > MAX_CANDIDATOS_VEREADOR) {
        fprintf(stderr, "Número de candidatos a vereador fora do intervalo permitido\n");
        return EXIT_FAILURE;
    }

    int numPrefeitos = carregarCandidatosPrefeito(prefeitos, "prefeitos.txt");
    if (numPrefeitos < MIN_CANDIDATOS_PREFEITO || numPrefeitos > MAX_CANDIDATOS_PREFEITO) {
        fprintf(stderr, "Número de candidatos a prefeito fora do intervalo permitido\n");
        return EXIT_FAILURE;
    }

    int numEleitores = carregarEleitores(eleitores, "eleitores.txt");
    if (numEleitores < MIN_ELEITORES || numEleitores > MAX_ELEITORES) {
        fprintf(stderr, "Número de eleitores fora do intervalo permitido\n");
        return EXIT_FAILURE;
    }

    votar(eleitores, numEleitores, vereadores, numVereadores, prefeitos, numPrefeitos);
    apurar();

    return EXIT_SUCCESS;
}
