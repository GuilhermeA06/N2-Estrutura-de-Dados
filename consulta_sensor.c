
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHA 256

typedef struct {
    long timestamp;
    char valor[64];
} Leitura;

long converter_data_para_timestamp(int dia, int mes, int ano, int hora, int minuto, int segundo) {
    struct tm tempo = {0};
    tempo.tm_year = ano - 1900;
    tempo.tm_mon = mes - 1;
    tempo.tm_mday = dia;
    tempo.tm_hour = hora;
    tempo.tm_min = minuto;
    tempo.tm_sec = segundo;
    return mktime(&tempo);
}

long calcular_diferenca(long a, long b) {
    return (a > b) ? (a - b) : (b - a);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: ./consulta <nome_sensor>
");
        return 1;
    }

    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "sensor_%s.txt", argv[1]);

    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo do sensor");
        return 1;
    }

    Leitura leituras[10000];
    int total = 0;

    while (fscanf(arquivo, "%ld %s", &leituras[total].timestamp, leituras[total].valor) == 2) {
        total++;
    }
    fclose(arquivo);

    int dia, mes, ano, hora, minuto, segundo;
    scanf("%d/%d/%d %d:%d:%d", &dia, &mes, &ano, &hora, &minuto, &segundo);

    long alvo = converter_data_para_timestamp(dia, mes, ano, hora, minuto, segundo);

    int esquerda = 0, direita = total - 1;
    int mais_proximo = -1;
    long menor_diferenca = __LONG_MAX__;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        long diferenca = calcular_diferenca(leituras[meio].timestamp, alvo);

        if (diferenca < menor_diferenca) {
            menor_diferenca = diferenca;
            mais_proximo = meio;
        }

        if (leituras[meio].timestamp < alvo) {
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }

    if (mais_proximo != -1) {
        printf("%ld %s\n", leituras[mais_proximo].timestamp, leituras[mais_proximo].valor);
    }

    return 0;
}
