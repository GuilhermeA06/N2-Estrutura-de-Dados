# N2-Estrutura-de-DadoS  
Projeto de Processamento de Dados de Sensores

## Descrição

Este projeto contém três programas em linguagem C que processam dados de sensores coletados em uma planta industrial inteligente. Os programas realizam as seguintes funções:

- **organizador_dados:** Lê os dados dos sensores a partir de um arquivo, armazena, e gera arquivos separados para cada sensor com as leituras organizadas em ordem crescente pelo timestamp.
- **gerador_teste:** Realiza busca binária para encontrar um valor específico em um arquivo de dados já ordenados (ordem crescente ou decrescente, conforme ajuste).
- **consulta_sensor:** Processa arquivos de dados de sensores considerando o tipo do dado (inteiro, float, string ou booleano) indicado via argumento, para realizar operações específicas.

## Requisitos

- Compilador C (ex: gcc)  
- Sistema operacional com terminal (Linux, macOS ou Windows com WSL/Git Bash)  
- Arquivos de entrada no formato especificado (ver seção "Formato dos Arquivos de Entrada")

## Formato dos Arquivos de Entrada

Cada linha do arquivo deve seguir o padrão:

<Timestamp> <ID_SENSOR> <TIPO> <VALOR>

- **Timestamp:** Representado em Unix Epoch (segundos desde 1 de janeiro de 1970)  
- **ID_SENSOR:** Identificador do sensor (string sem espaços)  
- **TIPO:** Tipo do dado coletado (ex: inteiro, float, string, booleano)  
- **VALOR:** Valor medido pelo sensor, coerente com o tipo indicado  

### Exemplo de arquivo de entrada

1622471123 sensor1 inteiro 25
1622471189 sensor1 inteiro 30
1622471150 sensor2 float 12.5

## Como Compilar

No terminal, dentro da pasta do projeto, compile os programas com:

```bash
gcc programa1.c -o programa1
gcc programa2.c -o programa2
gcc programa3.c -o programa3
Como Executar
Programa 1 (organizador_dados):

bash
Copiar
Editar
./programa1 arquivo_de_entrada.txt
Gera arquivos separados para cada sensor, com os dados organizados por timestamp crescente.

Programa 2 (gerador_teste):

./programa2 arquivo_ordenado.txt valor_a_buscar
Busca o valor especificado no arquivo ordenado.

Programa 3 (consulta_sensor):

./programa3 tipo_de_dado arquivo_de_entrada.txt
Executa operações específicas considerando o tipo de dado informado:

CONJ_Z para inteiro

CONJ_Q para float

TEXTO para string

BINARIO para booleano

Autor
Guilherme Andrade e Silva

Licença
Este projeto é de uso acadêmico e pessoal.
