#include "structs.h"
#include <locale.h> 

int carregarCandidatosVereador(Vereador *candidatos, const char *filename) {
    Vereador unico; // Estrutura temporária para armazenar dados de um candidato
    char *caractere_nao_convertido; // Ponteiro usado na conversão de strings para números

    char linha[118]; // Buffer para armazenar linhas lidas do arquivo
    char nome[50]; // Buffer para armazenar o nome do candidato
    char titulo[4]; // Buffer para armazenar o número do candidato
    char partido[3]; // Buffer para armazenar o número do partido
    char sigla[6]; // Buffer para armazenar a sigla do partido
    FILE *file = fopen(filename, "r"); // Abre o arquivo para leitura
    if (!file) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de candidatos a vereador");
        return -1; // Retorna erro em caso de falha ao abrir o arquivo
    }

    int count = 0; // Contador de candidatos
    while (fgets(linha, sizeof(linha), file)) { // Lê uma linha do arquivo por vez
        sscanf(linha, "%s %s %s %s\n", nome, titulo, partido, sigla); // Lê os dados da linha

        // Converte os valores de string para os tipos corretos e armazena na estrutura temporária
        unico.numero = strtol(titulo, &caractere_nao_convertido, 10);
        unico.numero_partido = strtol(partido, &caractere_nao_convertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
        snprintf(unico.sigla_partido, sizeof(unico.sigla_partido), "%s", sigla); 
        
        // Armazena a estrutura temporária no array de candidatos
        candidatos[count] = unico;
        
        count++; // Incrementa o contador de candidatos
    }
    
    fclose(file); // Fecha o arquivo
    return count; // Retorna o número de candidatos carregados
}

int carregarCandidatosPrefeito(Prefeito *candidatos, const char *filename) {
    Prefeito unico; // Estrutura temporária para armazenar dados de um candidato
    char *caractere_nao_convertido; // Ponteiro usado na conversão de strings para números

    char linha[118]; // Buffer para armazenar linhas lidas do arquivo
    char nome[50]; // Buffer para armazenar o nome do candidato
    char titulo[4]; // Buffer para armazenar o número do candidato
    char sigla[6]; // Buffer para armazenar a sigla do partido
    FILE *file = fopen(filename, "r"); // Abre o arquivo para leitura
    if (!file) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de candidatos a prefeito");
        return -1; // Retorna erro em caso de falha ao abrir o arquivo
    }

    int count = 0; // Contador de candidatos
    while (fgets(linha, sizeof(linha), file)) { // Lê uma linha do arquivo por vez
        sscanf(linha, "%s %s %s\n", nome, titulo, sigla); // Lê os dados da linha

        // Converte os valores de string para os tipos corretos e armazena na estrutura temporária
        unico.numero = strtol(titulo, &caractere_nao_convertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
        snprintf(unico.sigla_partido, sizeof(unico.sigla_partido), "%s", sigla); 
        
        // Armazena a estrutura temporária no array de candidatos
        candidatos[count] = unico;
        
        count++; // Incrementa o contador de candidatos
    }

    fclose(file); // Fecha o arquivo
    return count; // Retorna o número de candidatos carregados
}

int carregarEleitores(Eleitor *eleitores, const char *filename) {
    Eleitor unico; // Estrutura temporária para armazenar dados de um eleitor
    char *caractere_nao_convertido; // Ponteiro usado na conversão de strings para números

    char linha[118]; // Buffer para armazenar linhas lidas do arquivo
    char nome[50]; // Buffer para armazenar o nome do eleitor
    char titulo[6]; // Buffer para armazenar o título do eleitor
    char compareceu[2]; // Buffer para armazenar se o eleitor compareceu
    char deficiencia[2]; // Buffer para armazenar se o eleitor possui deficiência
    FILE *file = fopen(filename, "r"); // Abre o arquivo para leitura
    if (!file) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de eleitores");
        return -1; // Retorna erro em caso de falha ao abrir o arquivo
    }

    int count = 0; // Contador de eleitores
    while (fgets(linha, sizeof(linha), file)) { // Lê uma linha do arquivo por vez
        sscanf(linha, "%s %s %s %s\n", nome, titulo, deficiencia, compareceu); // Lê os dados da linha

        // Converte os valores de string para os tipos corretos e armazena na estrutura temporária
        unico.tituloDeEleitor = strtol(titulo, &caractere_nao_convertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
        snprintf(unico.compareceu, sizeof(unico.compareceu), "%s", compareceu); 
        snprintf(unico.deficiencia, sizeof(unico.deficiencia), "%s", deficiencia);
        
        // Armazena a estrutura temporária no array de eleitores
        eleitores[count] = unico;
        
        count++; // Incrementa o contador de eleitores
    }

    fclose(file); // Fecha o arquivo
    return count; // Retorna o número de eleitores carregados
}

void votar(Eleitor *eleitores, int *numEleitores, Vereador *vereadores, int *numVereadores, Prefeito *prefeitos, int *numPrefeitos, const char *filename) {
    int i;
    int count = 0;
    char linha[118]; // Buffer para armazenar linhas lidas do arquivo
    char nome[50]; // Buffer para armazenar o nome do eleitor
    char titulo[6]; // Buffer para armazenar o título do eleitor
    char compareceu[2]; // Buffer para armazenar se o eleitor compareceu
    char deficiencia[2]; // Buffer para armazenar se o eleitor possui deficiência
    int caractere_nao_convertido; // Variável usada na conversão de strings para números

    FILE *votosFile = fopen("votos.bin", "wb"); // Abre o arquivo binário de votos para escrita
    if (!votosFile) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de votos");
        return;
    }

    Eleitor unico; // Estrutura temporária para armazenar dados de um eleitor

    FILE *file = fopen(filename, "r"); // Abre o arquivo de eleitores para leitura
    if (!file) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de texto");
        return;
    }

    while (fgets(linha, sizeof(linha), file)) { // Lê uma linha do arquivo por vez
        sscanf(linha, "%s %s %s %s\n", nome, titulo, deficiencia, compareceu); // Lê os dados da linha

        // Converte os valores de string para os tipos corretos e armazena na estrutura temporária
        unico.tituloDeEleitor = strtol(titulo, &caractere_nao_convertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
        snprintf(unico.compareceu, sizeof(unico.compareceu), "%s", compareceu); 
        snprintf(unico.deficiencia, sizeof(unico.deficiencia), "%s", deficiencia);
        
        // Armazena a estrutura temporária no array de eleitores
        eleitores[count] = unico;
        
        count++; // Incrementa o contador de eleitores
    }
    fclose(file); // Fecha o arquivo de eleitores

    for (i = 0; i <= sizeof(numEleitores); i++) { // Itera sobre todos os eleitores
        if (eleitores[i].compareceu[0] == 'n') { // Verifica se o eleitor ainda não votou
            printf("Eleitor %s (%d) votando...\n", eleitores[i].nome, eleitores[i].tituloDeEleitor);

            int votoVereador = 0, votoPrefeito = 0;

            // Solicita o voto para vereador e prefeito
            printf("Digite o número do candidato a vereador ou 0 para voto em branco: ");
            scanf("%d", &votoVereador);
            printf("Digite o número do candidato a prefeito ou 0 para voto em branco: ");
            scanf("%d", &votoPrefeito);

            Voto voto; // Estrutura para armazenar os votos
            voto.voto_prefeito = votoPrefeito;
            voto.voto_vereador = votoVereador;

            // Grava o voto no arquivo binário
            fwrite(&voto, sizeof(Voto), 1, votosFile);
            eleitores[i].compareceu[i] = 's'; // Marca que o eleitor votou
        }
    }

    fclose(votosFile); // Fecha o arquivo binário de votos
}

void apurar() {
    int i;
    FILE *votosFile = fopen("votos.bin", "rb"); // Abre o arquivo binário de votos para leitura
    if (!votosFile) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de votos");
        return;
    }

    Voto voto; // Estrutura para armazenar um voto lido do arquivo
    int totalVotosVereador[1000] = {0}; // Array para contar os votos para cada vereador
    int totalVotosPrefeito[100] = {0}; // Array para contar os votos para cada prefeito

    while (fread(&voto, sizeof(voto), 1, votosFile) == 1) { // Lê os votos do arquivo binário
        if (voto.voto_vereador >= 0 && voto.voto_vereador < 1000) {
            totalVotosVereador[voto.voto_vereador]++; // Incrementa o contador de votos para o vereador
        }
        if (voto.voto_prefeito >= 0 && voto.voto_prefeito < 100) {
            totalVotosPrefeito[voto.voto_prefeito]++; // Incrementa o contador de votos para o prefeito
        }
    }

    fclose(votosFile); // Fecha o arquivo binário de votos

    FILE *resultadoFile = fopen("resultado.txt", "w"); // Abre o arquivo de resultados para escrita
    if (!resultadoFile) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir arquivo de resultados");
        return;
    }

    // Escreve os resultados da votação para vereador no arquivo de resultados
    fprintf(resultadoFile, "Resultados para Vereador:\n");
    for (i = 0; i < 1000; i++) {
        if (totalVotosVereador[i] > 0) {
            fprintf(resultadoFile, "Número: %d, Votos: %d\n", i, totalVotosVereador[i]);
        }
    }

    // Escreve os resultados da votação para prefeito no arquivo de resultados
    fprintf(resultadoFile, "\nResultados para Prefeito:\n");
    for (i = 0; i < 100; i++) {
        if (totalVotosPrefeito[i] > 0) {
            fprintf(resultadoFile, "Número: %d, Votos: %d\n", i, totalVotosPrefeito[i]);
        }
    }

    fclose(resultadoFile); // Fecha o arquivo de resultados
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // Define a localidade para suporte a caracteres especiais

    Vereador vereadores[MAX_CANDIDATOS_VEREADOR]; // Array para armazenar os candidatos a vereador
    Prefeito prefeitos[MAX_CANDIDATOS_PREFEITO]; // Array para armazenar os candidatos a prefeito
    Eleitor eleitores[MAX_ELEITORES]; // Array para armazenar os eleitores
    int numVereadores = 0; // Número de candidatos a vereador
    int numPrefeitos = 0; // Número de candidatos a prefeito
    int numEleitores = 0; // Número de eleitores

    // Carrega os candidatos a vereador a partir do arquivo "vereadores.txt"
    numVereadores = carregarCandidatosVereador(vereadores, "vereadores.txt");
    if (numVereadores < MIN_CANDIDATOS_VEREADOR || numVereadores > MAX_CANDIDATOS_VEREADOR) {
        fprintf(stderr, "Número de candidatos a vereador fora do intervalo permitido\n");
        return 1;
    }

    // Carrega os candidatos a prefeito a partir do arquivo "prefeitos.txt"
    numPrefeitos = carregarCandidatosPrefeito(prefeitos, "prefeitos.txt");
    if (numPrefeitos < MIN_CANDIDATOS_PREFEITO || numPrefeitos > MAX_CANDIDATOS_PREFEITO) {
        fprintf(stderr, "Número de candidatos a prefeito fora do intervalo permitido\n");
        return 1;
    }

    // Carrega os eleitores a partir do arquivo "eleitores.txt"
    numEleitores = carregarEleitores(eleitores, "eleitores.txt");
    if (numEleitores < MIN_ELEITORES || numEleitores > MAX_ELEITORES) {
        fprintf(stderr, "Número de eleitores fora do intervalo permitido\n");
        return 1;
    }

    // Chama a função para registrar os votos
    votar(&eleitores, &numEleitores, &vereadores, &numVereadores, &prefeitos, &numPrefeitos, "eleitores.txt");

    // Chama a função para apurar e gravar os resultados
    apurar();

    return 0; // Retorna sucesso
}