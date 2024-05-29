#include "structs.h"
#include <locale.h>

int carregarCandidatosVereador(Vereador *candidatos, const char *filename) {
	
	Vereador unico;
	char *caractere_nao_convertido;
	
	char linha[118];
	char nome[20];
	char titulo[4];
	char partido[3];
	char sigla[6];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de candidatos a vereador");
        return -1;
    }

    int count = 0;
    while(fgets(linha, sizeof(linha), file)){
    	//printf("\nsaiu do arquivo .txt      : %s",linha);// importante para debug
        sscanf(linha, "%s %s %s %s\n", nome, titulo,partido,sigla); 
        //printf("%s,%s,%s,%s\n",nome,titulo,partido,sigla) ;
        
        unico.numero = strtol(titulo, &caractere_nao_convertido, 10);
        unico.numero_partido = strtol(partido, &caractere_nao_convertido,10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
		snprintf(unico.sigla_partido, sizeof(unico.sigla_partido), "%s", sigla); 
		
		candidatos[count] = unico;
		//printf("reg %s,%d,%s,%s\n",candidatos[count].nome,candidatos[count].numero,candidatos[count].numero_partido,candidatos[count].sigla_partido) ;
		   
     	//if (count==3) break;		        	
         count++; 
	}
	
//    while (fscanf(file, "%s,%d,%d,%9s\n", 
//                  candidatos[count].nome, 
//                  &candidatos[count].numero, 
//                  &candidatos[count].numero_partido, 
//                  candidatos[count].sigla_partido) != EOF) {
//           printf("%s,%d,%d,%s\n",candidatos[count].nome, 
//                  candidatos[count].numero, 
//                  candidatos[count].numero_partido, 
//                  candidatos[count].sigla_partido) ;
//		if (count==3) break;		        	
//        count++;
//    }

    fclose(file);
    return count;
}

int carregarCandidatosPrefeito(Prefeito *candidatos, const char *filename) {
    Prefeito unico;
	char *caractere_nao_convertido;
	
	char linha[118];
	char nome[20];
	char titulo[4];
	char partido[3];
	char sigla[6];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de candidatos a prefeito");
        return -1;
    }
	
	int count = 0;
	while(fgets(linha, sizeof(linha), file)){
    	//printf("\nsaiu do arquivo .txt      : %s",linha);// importante para debug
        sscanf(linha, "%s %s %s\n", nome, titulo,sigla); 
        //printf("%s,%s,%s\n",nome,titulo,sigla);
        
        unico.numero = strtol(titulo, &caractere_nao_convertido, 10);
//        unico.numero_partido = strtol(partido, &caractere_nao_convertido,10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
		snprintf(unico.sigla_partido, sizeof(unico.sigla_partido), "%s", sigla); 
		
		candidatos[count] = unico;
		//printf("reg %s,%d,%s\n",candidatos[count].nome,candidatos[count].numero,candidatos[count].sigla_partido) ;
		   
     	//if (count==3) break;		        	
         count++; 
	}

//    int count = 0;
//    while (fscanf(file, "%s,%d,%9s\n", 
//                  candidatos[count].nome, 
//                  &candidatos[count].numero, 
//                  candidatos[count].sigla_partido) != EOF) {
//        count++;
//    }

    fclose(file);
    return count;
}

int carregarEleitores(Eleitor *eleitores, const char *filename) {
    Eleitor unico;
	char *caractere_nao_convertido;
	
	char linha[118];
	char nome[20];
	char titulo[4];
	char partido[3];
	char sigla_comp[2];
	char sigla_defi[2];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de candidatos a vereador");
        return -1;
    }

    int count = 0;
    while(fgets(linha, sizeof(linha), file)){
    	printf("\nsaiu do arquivo .txt      : %s",linha);// importante para debug
        sscanf(linha, "%s %s %s %s\n", nome, titulo,sigla_comp,sigla_defi); 
        printf("%s,%s,%s,%s\n",nome,titulo,sigla_comp,sigla_defi) ;
        
        unico.titulo = strtol(titulo, &caractere_nao_convertido, 10);
        snprintf(unico.nome, sizeof(unico.nome), "%s", nome);  
		snprintf(unico.compareceu, sizeof(unico.compareceu), "%s", sigla_comp); 
		snprintf(unico.deficiencia, sizeof(unico.deficiencia), "%s", sigla_defi);
		
		eleitores[count] = unico;
		printf("reg %s,%d,%s,%s\n",eleitores[count].nome,eleitores[count].titulo,eleitores[count].deficiencia,eleitores[count].compareceu);
		   
     	if (count==3) break;		        	
         count++; 
	}

//    int count = 0;
//    while (fscanf(file, "%s,%d,%c,%c\n", 
//                  eleitores[count].nome, 
//                  &eleitores[count].titulo, 
//                  &eleitores[count].deficiencia, 
//                  &eleitores[count].compareceu) != EOF) {
//        count++;
//    }

    fclose(file);
    return count;
}

void votar(Eleitor *eleitores, int numEleitores, Vereador *vereadores, int numVereadores, Prefeito *prefeitos, int numPrefeitos) {
    int i;
    //printf("teste1");
    FILE *votosFile = fopen("votos.bin", "wb");
    if (!votosFile) {
        perror("Erro ao abrir arquivo de votos");
        return;
    }
//printf("teste2");
    for (i = 0; i < numEleitores; i++) {
        if (eleitores[i].compareceu == 'N') {
            printf("Eleitor %s (%d) votando...\n", eleitores[i].nome, eleitores[i].titulo);
            int votoVereador, votoPrefeito;
            printf("Digite o Número do candidato a vereador ou 0 para voto branco: ");
            scanf("%d", &votoVereador);
            printf("Digite o Número do candidato a prefeito ou 0 para voto branco: ");
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

int apurar() {
    int i;
    FILE *votosFile = fopen("votos.bin", "rb");
    if (!votosFile) {
        perror("Erro ao abrir arquivo de votos");
        return -1;
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
        return -1;
    }

    fprintf(resultadoFile, "Resultados para Vereador:\n");
    for (i = 0; i < 1000; i++) {
        if (totalVotosVereador[i] > 0) {
            fprintf(resultadoFile, "Número: %d, Votos: %d\n", i, totalVotosVereador[i]);
        }
    }

    fprintf(resultadoFile, "\nResultados para Prefeito:\n");
    for (i = 0; i < 100; i++) {
        if (totalVotosPrefeito[i] > 0) {
            fprintf(resultadoFile, "Número: %d, Votos: %d\n", i, totalVotosPrefeito[i]);
        }
    }

    fclose(resultadoFile);
}

int main() {
    setlocale(LC_ALL,"Portuguese");

    Vereador vereadores[MAX_CANDIDATOS_VEREADOR];
    Prefeito prefeitos[MAX_CANDIDATOS_PREFEITO];
    Eleitor eleitores[MAX_ELEITORES];
    int numVereadores = -1;
    int numPrefeitos = -1;
    int numEleitores = -1;


    // numVereadores = carregarCandidatosVereador(vereadores, "vereadores.txt");
    // printf("numVereadores %d\n",numVereadores);
    // if (numVereadores < MIN_CANDIDATOS_VEREADOR || numVereadores > MAX_CANDIDATOS_VEREADOR) {
    //     fprintf(stderr, "Número de candidatos a vereador fora do intervalo permitido\n");
    //    printf("teste4");getchar();
    //     return 1;
    // }

    // numPrefeitos = carregarCandidatosPrefeito(prefeitos, "prefeitos.txt");
    // printf("numPrefeitos %d\n",numPrefeitos);
    // if (numPrefeitos < MIN_CANDIDATOS_PREFEITO || numPrefeitos > MAX_CANDIDATOS_PREFEITO) {
    //     fprintf(stderr, "Número de candidatos a prefeito fora do intervalo permitido\n");
    //   printf("teste5");getchar();
    //     return 1;
    // }
    numEleitores = carregarEleitores(eleitores, "eleitores.txt");
    printf("numEleitores %d\n",numEleitores);
    if (numEleitores < MIN_ELEITORES || numEleitores > MAX_ELEITORES) {
        fprintf(stderr, "Número de eleitores fora do intervalo permitido\n");
   printf("teste6");getchar();
        return 1;
    }
    
    printf("teste3");getchar();
    votar(eleitores, numEleitores, vereadores, numVereadores, prefeitos, numPrefeitos);
    printf("%d",apurar());
	apurar();

    return 0;
}