base
====
Programa simpes de conversão de bases que segue a filosofia UNIX. Aceita qualquer 
valor inteiro de 32 bits (entre 0 e 4,294,967.295, em decimal) e converte para 
qualquer valor nessa mesma faixa.

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
* de decimal para hexadecimal:
  ```
  $ base 10 16 1337
  ```

* de hexadecimal para binário:
  ```
  $ base 16 2 DEaDBeEF
  ```
  
etc