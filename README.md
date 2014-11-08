base
====
Programa simpes de conversão de bases que segue a filosofia UNIX. Aceita qualquer 
valor inteiro de 32 bits (entre 0 e 4,294,967.295, em decimal) e converte para 
qualquer valor nessa mesma faixa. Aceita bases entre 2 e 36, devido a limitação
representativa de 10 dígitos (0-9) + 26 letras (a-z ou A-Z).

## Instalação
Clone esse repositório e compile utilizando qualquer compilador compativel com 
o padrão C99. Aqui usaremos gcc como exemplo:

    $ gcc -std=c99 base.c -o base

Depois de compilado, dependendo do seu sistema, mude as permissões de uso para
execução:

    $ chmod +x base

## Modo de uso
    $ base [base de entrada] [base de saída] [valor numérico]

Exemplos:
* convertendo de decimal para hexadecimal:
  ```
  $ base 10 16 1337
  ```

* convertendo de hexadecimal para binário:
  ```
  $ base 16 2 DEadBEff
  ```
  
* criando um arquivo "arquivo.txt" com o resultadado da conversão hexadecimal
0xFF00 para decimal, redirecionando o STDIN para o arquivo.
  ```
  $ base 16 10 FF00>arquivo.txt
  ``` 
etc
