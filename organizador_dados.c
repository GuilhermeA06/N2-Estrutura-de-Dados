#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_LINHA 256
#define QUANTIDADE_MAXIMA_SENSORES 100
#define TAMANHO_INICIAL_LEITURAS 100

typedef struct {
    long dataEpoch;              
    char dadoLido[64];            
} RegistroDeLeitura;

typedef struct {
    char nomeSensor[50];      
    char tipoDado[16];           
    RegistroDeLeitura* listaDeLeituras;
    int quantidadeDeLeituras;
    int capacidadeAlocada;
} DadosDoSensor;


int ordenarPorDataCrescente(const void* a, const void* b) {
    RegistroDeLeitura* leituraA = (RegistroDeLeitura*)a;
    RegistroDeLeitura* leituraB = (RegistroDeLeitura*)b;
    return (leituraA->dataEpoch > leituraB->dataEpoch) - (leituraA->dataEpoch < leituraB->dataEpoch);
}


int encontrarSensorPorNome(DadosDoSensor sensores[], int total, const char* nomeProcurado) {
    for (int i = 0; i < total; i++) {
        if (strcmp(sensores[i].nomeSensor, nomeProcurado) == 0)
            return i;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso correto: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    FILE* arquivoEntrada = fopen(argv[1], "r");
    if (!arquivoEntrada) {
        perror("Erro: não foi possível abrir o arquivo de entrada");
        return 1;
    }

    DadosDoSensor sensores[QUANTIDADE_MAXIMA_SENSORES];
    int totalSensores = 0;

    char linhaLida[TAMANHO_MAXIMO_LINHA];

    while (fgets(linhaLida, sizeof(linhaLida), arquivoEntrada)) {
        long dataEpoch;
        char nomeSensor[50], tipoDado[16], valorLido[64];

        if (sscanf(linhaLida, "%ld %s %s %s", &dataEpoch, nomeSensor, tipoDado, valorLido) != 4) {
            continue;  
        }

        int indiceSensor = encontrarSensorPorNome(sensores, totalSensores, nomeSensor);
        if (indiceSensor == -1) {
            if (totalSensores >= QUANTIDADE_MAXIMA_SENSORES) {
                printf("Limite de sensores atingido.\n");
                return 1;
            }

            strcpy(sensores[totalSensores].nomeSensor, nomeSensor);
            strcpy(sensores[totalSensores].tipoDado, tipoDado);
            sensores[totalSensores].listaDeLeituras = malloc(sizeof(RegistroDeLeitura) * TAMANHO_INICIAL_LEITURAS);
            sensores[totalSensores].capacidadeAlocada = TAMANHO_INICIAL_LEITURAS;
            sensores[totalSensores].quantidadeDeLeituras = 0;
            indiceSensor = totalSensores++;
        }

        DadosDoSensor* sensorAtual = &sensores[indiceSensor];
        if (sensorAtual->quantidadeDeLeituras >= sensorAtual->capacidadeAlocada) {
            sensorAtual->capacidadeAlocada *= 2;
            sensorAtual->listaDeLeituras = realloc(
                sensorAtual->listaDeLeituras,
                sizeof(RegistroDeLeitura) * sensorAtual->capacidadeAlocada
            );
        }

        sensorAtual->listaDeLeituras[sensorAtual->quantidadeDeLeituras].dataEpoch = dataEpoch;
        strcpy(sensorAtual->listaDeLeituras[sensorAtual->quantidadeDeLeituras].dadoLido, valorLido);
        sensorAtual->quantidadeDeLeituras++;
    }

    fclose(arquivoEntrada);

    for (int i = 0; i < totalSensores; i++) {
        DadosDoSensor* sensorAtual = &sensores[i];

        qsort(sensorAtual->listaDeLeituras,
              sensorAtual->quantidadeDeLeituras,
              sizeof(RegistroDeLeitura),
              ordenarPorDataCrescente);

        char nomeArquivoSaida[100];
        sprintf(nomeArquivoSaida, "sensor_%s.txt", sensorAtual->nomeSensor);

        FILE* arquivoSaida = fopen(nomeArquivoSaida, "w");
        if (!arquivoSaida) {
            perror("Erro ao criar arquivo do sensor");
            continue;
        }

        for (int j = 0; j < sensorAtual->quantidadeDeLeituras; j++) {
            fprintf(
                arquivoSaida,
                "%ld %s\n",
                sensorAtual->listaDeLeituras[j].dataEpoch,
                sensorAtual->listaDeLeituras[j].dadoLido
            );
        }

        fclose(arquivoSaida);
        free(sensorAtual->listaDeLeituras);
    }

    printf("Arquivos individuais dos sensores gerados com sucesso!\n");
    return 0;
}
