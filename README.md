# Trabalho Prático 2 - BCC203
---
### **Autores**:
* Carlos Eduardo Gonzaga Romaniello de Souza
* Vinicius Gabriel Angelozzi Verona de Resende
  
---

### **Execução**
Para executar os testes mencionados no relatório, basta executar o seguinte comando baseado no sistema operacional de sua máquina:

>WINDOWS:
```bash
> cd script/
```
```bash
> execution.bat
```
Cada execução criará um arquivo `TXT` na pasta `scripts` seguindo a nomenclatura: `algoritmo_quantidade_ordenacao.txt` onde `ordenacao`.

Caso queira executar o programa manualmente e com os próprios parâmetros, basta seguir o exigido pelo professor Guilherme.

>WINDOWS:
```bash
> cd src/
```
```bash
> gcc *.c -o main.exe -Wall
```
```bash
> main.exe metodo quantidade ordem [-P]
```

>LINUX:
```bash
$ cd src/
```
```bash
$ gcc *.c -o main -Wall
```
```bash
$ ./main pesquisa quantidade ordem [-P]
```
>>PS: Como mencionado no relatório, o algoritmo QuickSort Externo não funciona em sistemas Linux.

---

### **Estruturação das Pastas**
Conforme mencionado no relatório presente na pasta raiz, os arquivos estão todos organizados em pastas. Para encontrar o arquivo que deseja, basta seguir o caminho abaixo:

> Codigo
* `scripts` - /scripts/
* `pré-ordenação dos arquivos` - /julia/sortInput.jl
* `código fonte` - /src/metodo_que_deseja.c
* `código header` - /src/metodo_que_deseja.h

> Árquivos
* `Textos` - /input/ (gerados após a execução do script em julia)
* `Fitas` - /src/Fitas/ (contem fitas utilizadas na execução do programa)
* `Resultado` - /src/Resultado/PROVAO_RESULTADO.txt (arquivo texto ordenado após execução do programa)
* `Estatisticas` - /estatisticas/metodo/metodo_quantidade_ordem_key*.txt -> (* = 1-10)

> Coleta de estatisticas
* `Códigos` - /julia/organizaDados.jl
* `Coleta feita` - /dados/método/quantidade-valor_ordenacao-valor.txt, onde `valor` é o valor de quantidade ou ordenação
* `Coleta usada em gráficos` - /dados/gráficos/criterio-quantidade-valor, onde `valor` é o valor de quantidade

> Gráficos
* `Gráficos comparações` - /graficos/comparacoes/qntd-quantidade/index.html
* `Gráficos escrita` - /graficos/escrita/qntd-quantidade/index.html
* `Gráficos leitura` - /graficos/leitura/qntd-quantidade/index.html
* `Gráficos tempo` - /graficos/tempo/qntd-quantidade/index.html

---

### **Observação**
Os gráficos presentes na pasta `/graficos`, apresentam as comparações dos critérios totais (comparações, leitura, escrita e tempo de execução) entre os métodos. Os dados individuais dos critérios durante as fases de pré-processamento dos dados e de ordenação, estão presentes na pasta `/dados/metodo`.

Esses dados são gerados ao final da execução do código independente do parâmetro `-P` ser passado ou não.