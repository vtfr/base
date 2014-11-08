/* gcc base.c -o base -std=c99 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Representa binário */
void representar_binario (unsigned int valor)
{
	/* 32 bits + 1 nul */
	char buffer[33];
	buffer[32] = '\0';
	
	/* i = byte to buffer = bit do valor */
	for (unsigned char i = 0; i < 32; i++)
		buffer[31 - i] = (valor & (1 << i)) ? '1' : '0';
	
	/* Remove bits desnecessários incrementando o início da string, caso o bit
	   seja zero. 
	   
	   Demostração prática:
	   
	   00000000000010000010000000010001
	   ↓
	   INICIO DA STRING
	   
	   ...

	   00000000000010000010000000010001
	               ↓
	               INICIO DA STRING
	*/
	char *inicio = buffer;
	
	/* Procura um dígito '1' */
	while (*inicio && *inicio != '1')
		inicio++;
	
	/* Caso tenhamos chegagado ao último caracter da string sem achar um '1'
	   sequer, volta o ponteiro um caracter para representar o último zero 
	*/
	if (!*inicio)
		inicio--;
	
	/* Desenha */
	printf("%s\n", inicio);
}



/* Verifica se uma string é um inteiro */
unsigned char verificar_inteiro (char *string)
{
	/* Trivial */
	while (*string)
	{
		/* Caracter está entre '0' e '9' */
		if (*string < '0' || *string > '9')
			return 0;

		string++;
	}

	return 1;
}



/* Converte uma string para um valor de base. 
   Essa função funciona, sim, mas é 80/20
   
   TODO implementar unário
*/
unsigned char converter_string_base (char *string)
{
	/* Caso o ponteiro seja nulo */
	if (!string)
		return 0;

	/* Caso a string seja um valor numérico, converte-a para um inteiro */
	if (verificar_inteiro(string))
		return atoi(string);
	
	/* Caso a string não seja um número, converte para um, utilizando a tabela
	   já feita. */
	     if (strcmp(string, "una") == 0) return 1;
	else if (strcmp(string, "bin") == 0) return 2;
	else if (strcmp(string, "oct") == 0) return 8;
	else if (strcmp(string, "dec") == 0) return 10;
	else if (strcmp(string, "hex") == 0) return 16;
	
	/* Caso não seja uma base válida */
	return 0;
}



int main (int argc, char *argv[])
{
	/* Caso o programa seja executado com um número de argumentos diferetentes
	   de 4, mostra a mensagem de uso. Vale lembrar que o nome do programa é
	   o argumento de número 0 
	*/
	if (argc != 4)
	{
		printf("Uso %s [BASE DE ENTRADA] [BASE DE SAIDA] valor\n"
		       "\n"
		       "Esse programa aceita qualquer base entre 2 e 16 como entrada, "
		       "mas restringe a saida para as bases 2, 8, 10 e 16.\n"
		       "\n"
		       "  Exemplo:\n"
		       "    %s 16 10 f044\n"
		       "    %s hex dec deadbeef\n"
		       "    %s 2 16 -10100111001\n"
		       "\n"
		       "Copyleft 2014 Victor Franco (https://github.com/vtfrvl/)\n",
		       argv[0], argv[0], 
		       argv[0], argv[0]);
		return 1;
	}
	
	/* Converte as bases e valida cada uma delas */
	unsigned char base_entrada, base_saida;
	base_entrada = converter_string_base(argv[1]);
	base_saida   = converter_string_base(argv[2]);
	
	if (!base_entrada || !base_saida)
	{
		printf("Base \"%s\" inválida.\n", base_entrada ? argv[2] : argv[1]);
		return 2;
	}
	
	if (base_entrada < 2 || base_entrada > 32)
	{
		printf("Base de entrada \"%s\" não está entre 2 e 16\n", argv[1]);
		return 3;
	}
	
	if (!(base_saida == 2  || base_saida == 8
	   || base_saida == 10 || base_saida == 16 ))
	{
		printf("Base de saida \"%s\" não é válida.\n"
		       "Bases de saida válidas: 2 (bin), 8 (oct), "
		       "10 (dec), 16 (hex)\n", argv[2]);
		return 4;
	}
	
	/* Converte a base.
		Essa parte do código tem um funcionamento interessante. Na função strtol,
		o segundo argumento é um ponteiro para um ponteiro, onde este último
		apontará para o último caracter lido. Se o último caracter lido for o
		último caracter da string que queremos ler, então a função conseguiu
		interpretar a string completamente.
	 */
	char *final;
	unsigned int valor = strtoul(argv[3], &final, base_entrada);

	/* Se o ponteiro para o final da string estiver, de fato, no final da
	   string... */
	if (*final != '\0')
	{
		printf("Valor \"%s\" inválido.\n", argv[3]);
		return 5;
	}
	
	/* Representa a string */
	switch (base_saida)
	{
		case 2:  representar_binario(valor); break;
		case 8:  printf("%o\n", valor);      break;
		case 10: printf("%u\n", valor);      break;
		case 16: printf("%X\n", valor);      break;
	}
	
	return 0;
}
