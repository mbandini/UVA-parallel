# PROGRAMAÇÃO PARALELA - UNIVERSIDADE VEIGA DE ALMEIDA - 2021-1

Este repositório contém um conjunto de códigos utilizados durante o curso da disciplina de Programação Paralela (2021-1) da Universidade Veiga de Almeida.

## Conteúdo

* Programação Paralela com Pthreads (diretório pthreads)
* Programação Paralela com OpenMP (diretório omp)
* Programação Paralela com MPI (diretório mpi)
* Gabaritos de avaliações (diretório gabaritos)

## Gabarito Atividade Individual (A1)

### Questão 1

Código presente no diretório "gabaritos"

### Questão 2

O paralelismo utilizado é o paralelismo de dados, uma vez que o processamento de encontrar os valores diferentes de zero é o mesmo realizado por todas as threads. Porém os dados processados por cada uma delas são diferentes, o que caracteriza paralelismo de dados (decomposição de domínio). Se quisermos caracterizar essa questão do ponto de vista da taxonomia de Flynn, ela se enquadra na classificação SIMD (Single Instruction Multiple Data).

### Questão 3

* Item A: Benefícios: proximidade entre os dados em memória e os núcleos de processamento, o que proporciona maior vazão de processamento. Além disso, permite especificar qual núcleo deve executar cada thread. Restrição: baixa escalalabilidade imposta pelas limitações físicas do chipset, o que não ocorre em arquiteturas de memória distribuída.

* Item B: pode-se aplicar diferentes configurações para os núcleos de um mesmo processador por meio da tecnologia DVFS. Assim, podemos atribuir o processamento de tarefas computacionalmente mais complexas para núcleos com a frequência mais elevada, enquanto atrbui processamentos mais simples aos núcleos com frequência de clock reduzida.

### Questão 4

* Item A: não é possível afirmar que as duas threads sao iguais ou diferentes, pelo fato de que, por exemplo, elas podem processar instruções diferentes (seriam diferentes), ou processar instruções, porém com dados diferentes (seriam iguais). Como não se conhece nem os dados, nem as instruções, as únicas coisas que se pode afirmar sobre cada uma delas é que elas são filhas da mesma thread e que cada uma possui uma thread filha.

* Item B: não é possível afirmar que há ou não paralelismo de dados, uma vez que os dados não são conhecidos. O mesmo valeria para o paralelismo de instruções, uma vez que elas também não são conhecidas.

## Desenvolvido e mantido pelo Prof. Matheus B. Bandini