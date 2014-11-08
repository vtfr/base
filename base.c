#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Representações numéricas; também conhecidas como dígitos */
char repr[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z'
};

/* Representa um número em uma base específica */
void representar_num_base (char *buffer, size_t size, uint32_t valor, uint8_t base)
{
	/* Caso seja fornecido um buffer inválido ou tenha tamanho menor que dois,
	   o que seria insuficiente para representar um dígito e terminar com NUL */
	if (!buffer || size < 2 || base < 2) return;
	
	/* Como trabalhamos com 32 bits e representação mínima de 2 bits, o tamanho
	   máximo de dígitos será 32 */
	uint8_t digits[32], digitsIndex = 0;
	
	/* Separa os digitos de trás para frente */
	do { digits[digitsIndex++] = valor % base; }
	while ((valor /= base) && digitsIndex < 32);
	
	/* Representa os dígitos na ordem correta voltando o index de dígitos. É
	   necessário o uso do pre-decremento, em digitsIndex, para acessar o byte
	   anterior ao index, o que seria uma leitura da memória no sentido inverso */
	do { *buffer++ = repr[digits[--digitsIndex]]; }
	while (digitsIndex && (--size > 1));
	
	/* Adiciona o NUL */
	*buffer = '\0';
}

/* Converte uma string para um valor de base */
uint8_t converter_string_base (char *string)
{
	if (!string)
		return 0;
		
	/* Converte nossa string. O segundo argumento determina a posição de término
	   da leitura na string fornecida no primeiro argumento. Se a posição for,
	   de fato, no fim da string (NUL), então a string foi lida corretamente */
	uint8_t base = strtol(string, &string, 10);	
	return *string == '\0' ? base : 0;
}



int main (int argc, char *argv[])
{
	char buffer[33];
	uint8_t base_entrada, base_saida;
	uint32_t valor;
	
	/* Caso o programa seja executado com um número de argumentos diferetentes
	   de 4, mostra a mensagem de uso. Vale lembrar que o nome do programa é
	   o argumento de número 0 */
	if (argc != 4)
	{
		printf("Uso %s [BASE DE ENTRADA] [BASE DE SAIDA] valor\n"
		       "\n"
		       "Programa simpes de conversão de bases que segue a filosofia UN"
		       "IX. Aceita qualquer valor inteiro de 32 bits (entre 0 e 4,967."
		       "295, em decimal) e converte para qualquer valor nessa mesma fa"
		       "ixa. Aceita bases entre 2 e 36, devido a limitação representat"
		       "iva de 10 digitos (0-9) + 26 letras (a-z ou A-Z)."
		       "\n"
		       "  Exemplo:\n"
		       "    %s 10 16 1028\n"
		       "    %s 16 10 deadbeef\n"
		       "    %s 2 16 10100111001\n"
		       "\n"
		       "2014 Victor \"vtfrvl\" Franco (https://github.com/vtfrvl/)\n",
		       argv[0], argv[0], argv[0], argv[0]);
		return 1;
	}
	
	/* Converte as bases e valida cada uma delas */
	base_entrada = converter_string_base(argv[1]);
	base_saida   = converter_string_base(argv[2]);
	
	/* Verifica as margens das bases de entrada/saida */
	if ((base_saida < 2   || base_saida > 36)
	 || (base_entrada < 2 || base_entrada > 36))
	{
		fprintf(stderr, "Base invalida. As bases devem ser "
		                "valores numéricos entre 2 e 36\n");
		return 2;
	}
	
	/* Lê a string de base. */
	valor = strtoul(argv[3], &argv[3], base_entrada);

	/* Verifica se toda a string foi lida corretamente */
	if (*argv[3] != '\0')
	{
		fprintf(stderr, "Fragmento \"%s\" inesperado.\n", argv[3]);
		return 3;
	}
	
	/* Imprime a representação numérica da base */
	representar_num_base(buffer, 32, valor, base_saida);
	puts(buffer);
	
	/* Retorna sucesso */
	return 0;
}
