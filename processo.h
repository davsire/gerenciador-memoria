#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct Pagina {
  int numero;
  int quadro;
  struct Pagina* prox;
} pagina_t;

typedef struct Processo {
  int id;
  int tamanho;
  pagina_t* paginas;
  struct Processo* prox;
  int mem_logica[];
} processo_t;

processo_t* criar_e_inserir_processo(int id, int tamanho, int qtd_paginas, processo_t** lista_processos);

processo_t* obter_processo_por_id(int id, processo_t* lista_processos);

pagina_t* criar_pagina_processo(processo_t* processo, int numero, int quadro);

#endif
