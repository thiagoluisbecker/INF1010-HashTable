# HashTable

Implementar algoritmos de busca, inclusão e exclusão em vetor de X posições (onde X é 
o maior número primo após 1024, ou 210), usando hashing com tratamento de colisão
para armazenar placas de automóveis no formato “CCCNNNN” onde C é um caractere 
maiúsculo e N um numeral. A rotina de tratamento de colisão deve armazenar a nova 
placa no próprio vetor (endereçamento interno). Não devem ser usadas outras estruturas 
de dados. A função hash deve ser definida individualmente e utilizar endereçamento 
aberto com tentativa linear, quadrática ou dispersão dupla.
Elaborar programa contendo a implementação dos algoritmos de inserção, exclusão e 
busca, em linguagem C. Os algoritmos devem prever uma entrada de dados via arquivo 
texto contendo placas de automóveis geradas aleatoriamente (em cada linha do arquivo 
texto deverá vir uma placa seguida pelos caracteres <cr> <lf>). O programa deve prever 
ainda a geração de um relatório indicando o total de colisões geradas e os tempos de 
inclusão e de busca a todos os elementos do vetor (a busca deve ser feita após o término 
da inclusão de todas as placas).
Deverá ser entregue ainda um relatório contendo o pseudocódigo dos algoritmos 
utilizados, os programas fonte, os tempos tomados para cada algoritmo e a geração do
gráfico de tamanho da entrada X tempo de execução de cada um, para diferentes valores 
de entrada por exemplo: 128, 256 e 512 placas (complexidade prática).
Todos os aspectos considerados deverão ser avaliados.
A avaliação vai ser feita em um mesmo equipamento para todos os grupos. A maior nota 
caberá ao grupo que fizer o trabalho completo, com menor número de colisões e menor 
tempo de execução dos algoritmos. Para a avaliação o professor fornecerá um arquivo de 
placas geradas aleatoriamente para servir de comparação entre os trabalhos (número de 
colisões e tempo de execução).
