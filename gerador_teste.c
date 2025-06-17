
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long gerar_timestamp_aleatorio(time_t inicio, time_t fim) {
    return inicio + rand() % (fim - inicio + 1);
}

void gerar_valor(char tipo[], char* destino) {
    if (strcmp(tipo, "CONJ_Z") == 0) {
        sprintf(destino, "%d", rand() % 1000);
    } else if (strcmp(tipo, "CONJ_Q") == 0) {
        sprintf(destino, "%.2f", ((float)rand() / RAND_MAX) * 1000);
    } else if (strcmp(tipo, "TEXTO") == 0) {
        int len = 1 + rand() % 16;
        for (int i = 0; i < len; i++) {
            destino[i] = 'A' + rand() % 26;
        }
        destino[len] = '\0';
    } else if (strcmp(tipo, "BINARIO") == 0) {
        sprintf(destino, "%s", rand() % 2 ? "true" : "false");
    } else {
        strcpy(destino, "null");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5 || (argc - 3) % 2 != 0) {
        printf("Uso: ./gerador <DD/MM/AAAA_HH:MM:SS_inicio> <DD/MM/AAAA_HH:MM:SS_fim> <SENSOR1> <TIPO1> [<SENSOR2> <TIPO2> ...]\n");
        return 1;
    }

    struct tm t_inicio = {0}, t_fim = {0};
    sscanf(argv[1], "%d/%d/%d_%d:%d:%d", &t_inicio.tm_mday, &t_inicio.tm_mon, &t_inicio.tm_year,
           &t_inicio.tm_hour, &t_inicio.tm_min, &t_inicio.tm_sec);
    t_inicio.tm_mon -= 1;
    t_inicio.tm_year -= 1900;

    sscanf(argv[2], "%d/%d/%d_%d:%d:%d", &t_fim.tm_mday, &t_fim.tm_mon, &t_fim.tm_year,
           &t_fim.tm_hour, &t_fim.tm_min, &t_fim.tm_sec);
    t_fim.tm_mon -= 1;
    t_fim.tm_year -= 1900;

    time_t inicio = mktime(&t_inicio);
    time_t fim = mktime(&t_fim);

    FILE* saida = fopen("dados_teste.txt", "w");
    srand(time(NULL));

    for (int i = 3; i < argc; i += 2) {
        char* nome = argv[i];
        char* tipo = argv[i + 1];

        for (int j = 0; j < 2000; j++) {
            long tempo = gerar_timestamp_aleatorio(inicio, fim);
            char valor[64];
            gerar_valor(tipo, valor);
            fprintf(saida, "%ld %s %s\n", tempo, nome, valor);
        }
    }

    fclose(saida);
    return 0;
}
