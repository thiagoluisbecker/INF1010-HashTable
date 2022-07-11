#include <stdio.h>
#include <string.h>
#include <time.h>

#define TAM 1031      // tamanho da tabela hash
#define numPrimo 257  // número a ser adicionada em caso de colisão

char hash[TAM][8];  // Cria uma matriz para armazenar placas
int colisaoInd;     // Variavel que armazena as colisões individuais
int colisaoTotal = 0;  // Variavel que armazena todas as colisões

int dispersaoHash(char placa[])
{
  int posHash = 0;  // Inicializa a posição com 0
	colisaoInd = 0;   // Zera o número de colisões de determinada placa
  
	for(int i = 0; i < 8; i++)
	{
		posHash += (i+1) * placa[i];
	}
	posHash = posHash % TAM;  // Aloca o número calculado dentro da Tabela Hash
    
  for(int j = 0; j < TAM; j++)
	{    
		if(strcmp(hash[posHash], "") == 0 || strcmp(hash[posHash],"REMOVED") == 0)	//Espaço vazio na tabela
		{
			return posHash;
		}
		if(strcmp(hash[posHash], placa) == 0)		//Chave duplicada
		{
			return posHash;
		}
		posHash += numPrimo;  //Colisão
		colisaoInd++;         // Incrimenta número de colisões de determinada placa
    colisaoTotal++;       // Incrementa número de colisões totais
    if(posHash >= TAM)    // Se a posição ultrapassar o espaço da Tabela Hash
		{
			posHash -= TAM;	    // Volta para dentro do espaço da Tabela Hash
		}
  }
    return -1;					//Não há espaço na tabela
}

void insereHash(char placa[])
{
	int pos;
  pos = dispersaoHash(placa);	//Pega posição na tabela Hash
	
	if(pos == -1)				//Se retornou -1 tabela está cheia
	{
		printf("Erro ao inserir placa %s\n", placa);
		return;
	}
	strcpy(hash[pos], placa);			//Insere placa na posição encontrada
}

int buscaHash(char placa[])
{
	int pos = dispersaoHash(placa);	//Pega posição na tabela Hash
  
  if(pos == -1)
	{
		printf("Elemento não está na tabela\n");
		return -1;				//Elemento não está na tabela, retorna -1
	}
	
	for(int i = 0; i < TAM; i++)
	{
		if(strcmp(hash[pos], placa) == 0)	//Se posição corresponder a placa
		{
			return pos;			//Retorna posição
		}
    if(strcmp(hash[pos], "") == 0) //Se chegar a um espaço vazio nunca preenchido significa que não está na Tabela Hash
    {
      return -1;  // Não está na tabela, retorna -1
    }
		pos += numPrimo;		//Se não, anda para o próximo elemento de acordo com regra de dispersão
    if(pos >= TAM)    // Se a posição ultrapassar o espaço da Tabela Hash
    {
      pos -= TAM;    // Volta para dentro do espaço da Tabela Hash
    }
	}
	
	return -1;					//Se não estiver na tabela, retorna -1
}

void excluiHash(char placa[])
{
	int pos = buscaHash(placa);	//Pega posição na tabela Hash
	if(pos != -1)        // Se encontrar um elemento
  {
		strcpy(hash[pos], "REMOVED");  // Substitui a placa por REMOVED
	}
  else
  {
    printf("%s - Elemento não está na tabela\n", placa); //Indica que não está na tabela
  }
}

int main(void)
{
  FILE *arq_entrada, *arq_saida_insercao, *arq_saida_busca, *arq_saida_exclusao;
  char placa[8];
  clock_t tempoIni,tempoFim;
  double difTempo, tempoTotal = 0, tempo128, tempo256, tempo512;
  int cont = 0, retBusca;
  
  arq_entrada = fopen("Dados de placas.txt", "r"); // Abre arquivo de placas em modo leitura
  if(arq_entrada == NULL)
  {
	printf("Erro ao abrir arquivo de entrada\n");
	return 1;
  }
  
  arq_saida_insercao = fopen("Relatorio Colisao", "w"); // Abre arquivo de colisões em modo escrita
  if(arq_saida_insercao == NULL)
  {
	printf("Erro ao abrir arquivo de colisao\n");
	return 1;
  }
  arq_saida_busca = fopen("Relatorio Busca", "w"); // Abre arquivo de busca em modo escrita
  if(arq_saida_busca == NULL)
  {
	printf("Erro ao abrir arquivo de busca\n");
	return 1;
  }
  arq_saida_exclusao = fopen("Relatorio Exclusao", "w"); // Abre arquivo de exclusões em modo escrita
  if(arq_saida_exclusao == NULL)
  {
	printf("Erro ao abrir arquivo de exclusao\n");
	return 1;
  }
  
  while(fscanf(arq_entrada, "%s", placa)!= EOF) //Le enquanto há linhas no arquivo
  {
    tempoIni = clock();  // Pega o valor atual de tempo
    insereHash(placa);   // Executa a inserção
    tempoFim = clock();  // Pega o valor atual de tempo
    difTempo = ((double) (tempoFim - tempoIni)) / CLOCKS_PER_SEC; // Calcula a diferença entre os tempos medidos
    tempoTotal += difTempo; // Soma o tempo de inserção da placa ao tempo total
    cont++;                 // Contabiliza a iteração
    if(cont == 128)
    {
      tempo128 = tempoTotal;  // Guarda o tempo decorrido após 128 iterações
    }
    else if(cont == 256)
    {
      tempo256 = tempoTotal;  // Guarda o tempo decorrido após 256 iterações
    }
    else if(cont == 512)
    {
      tempo512= tempoTotal;  // Guarda o tempo decorrido após 512 iterações
    }
    fprintf(arq_saida_insercao,"%s - Numero Colisoes: %d\tTempo de Inserção: %.16gs\n", placa, colisaoInd, difTempo);  // Insere no arquivo de inserções a placa, o número de colisões que ela teve e quanto tempo levou sua inserção
  }
  
  fprintf(arq_saida_insercao,"\nColisoes Totais: %d\n",colisaoTotal);
  fprintf(arq_saida_insercao, "Tempo decorrido de 128 inserções: %.16gs\n", tempo128);
  fprintf(arq_saida_insercao, "Tempo decorrido de 256 inserções: %.16gs\n", tempo256);
  fprintf(arq_saida_insercao, "Tempo decorrido de 512 inserções: %.16gs\n", tempo512);
  fprintf(arq_saida_insercao, "Tempo decorrido de %d inserções: %.16gs", cont, tempoTotal);

  rewind(arq_entrada);  // Coloca o ponteiro do arquivo novamente em seu começo
  cont = 0;  // Define o contador de iterações para 0
  tempoTotal = 0;  // Define o tempoTotal para 0
  while(fscanf(arq_entrada, "%s", placa)!= EOF) //Le enquanto há linhas no arquivo
  {
    tempoIni = clock();  // Pega o valor atual de tempo
    retBusca = buscaHash(placa);  // Executa a busca
    tempoFim = clock();  // Pega o valor atual de tempo
    difTempo = ((double) (tempoFim - tempoIni)) / CLOCKS_PER_SEC;  // Calcula a diferença entre os tempos medidos
    tempoTotal += difTempo;  // Soma o tempo de busca da placa ao tempo total 
    cont++;  // Contabiliza a iteração
    if(cont == 128)
    {
      tempo128 = tempoTotal;  // Guarda o tempo decorrido após 128 iterações
    }
    else if(cont == 256)
    {
      tempo256 = tempoTotal;  // Guarda o tempo decorrido após 256 iterações
    }
    else if(cont == 512)
    {
      tempo512= tempoTotal;  // Guarda o tempo decorrido após 512 iterações
    }
    if(retBusca == -1)  // Se a busca não encontrou a placa
    {
      fprintf(arq_saida_busca, "%s - Não Encontrado\tTempo de Busca: %.16gs\n", placa, difTempo);
    }
    else
    {
      fprintf(arq_saida_busca,"%s - Encontrado na Pos: %d\tTempo de Busca: %.16gs\n", placa, retBusca, difTempo);
    }
  }
  
  fprintf(arq_saida_busca, "Tempo decorrido de 128 buscas: %.16gs\n", tempo128);
  fprintf(arq_saida_busca, "Tempo decorrido de 256 buscas: %.16gs\n", tempo256);
  fprintf(arq_saida_busca, "Tempo decorrido de 512 buscas: %.16gs\n", tempo512);
  fprintf(arq_saida_busca, "Tempo decorrido de %d buscas: %.16gs", cont, tempoTotal);

  for(int i = 0; i < TAM; i++)
  {
      printf("Hash[%d]: %s\n", i, hash[i]);
  }

  rewind(arq_entrada);  // Coloca o ponteiro do arquivo novamente em seu começo
  cont = 0;  // Define o contador de iterações para 0
  tempoTotal = 0;  // Define o tempoTotal para 0
  while(fscanf(arq_entrada, "%s", placa)!= EOF)  //Le enquanto há linhas no arquivo
  {
    tempoIni = clock();  // Pega o valor atual de tempo
    excluiHash(placa);   // Executa a exclusão
    tempoFim = clock();  // Pega o valor atual de tempo
    difTempo = ((double) (tempoFim - tempoIni)) / CLOCKS_PER_SEC;  // Calcula a diferença entre os tempos medidos
    tempoTotal += difTempo;  // Soma o tempo de busca da placa ao tempo total 
    cont++;  // Contabiliza a iteração
    if(cont == 128)
    {
      tempo128 = tempoTotal;  // Guarda o tempo decorrido após 128 iterações
    }
    else if(cont == 256)
    {
      tempo256 = tempoTotal;  // Guarda o tempo decorrido após 256 iterações
    }
    else if(cont == 512)
    {
      tempo512= tempoTotal;  // Guarda o tempo decorrido após 512 iterações
    }
    fprintf(arq_saida_exclusao,"%s - Remoção Tratada\tTempo de Remoção: %.16gs\n", placa, difTempo);
  }
  
  fprintf(arq_saida_exclusao, "Tempo decorrido de 128 remoções: %.16gs\n", tempo128);
  fprintf(arq_saida_exclusao, "Tempo decorrido de 256 remoções: %.16gs\n", tempo256);
  fprintf(arq_saida_exclusao, "Tempo decorrido de 512 remoções: %.16gs\n", tempo512);
  fprintf(arq_saida_exclusao, "Tempo decorrido de %d remoções: %.16gs", cont, tempoTotal);
  
  fclose(arq_entrada);  // Fecha arquivo de entrada
  fclose(arq_saida_insercao);  // Fecha arquivo de inserção
  fclose(arq_saida_busca);     // Fecha arquivo de busca
  fclose(arq_saida_exclusao);  // Fecha arquivo de exclusão
  return 0;
}