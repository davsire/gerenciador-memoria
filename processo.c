#include <stdlib.h>
#include "processo.h"

#include <stdio.h>

processo_t* criar_e_inserir_processo(int id, int tamanho, processo_t** lista_processos) {
  processo_t* processo = (processo_t*) malloc(sizeof(processo_t));
  processo->id = id;
  processo->tamanho = tamanho;

  if (*lista_processos == NULL) {
    *lista_processos = processo;
    return processo;
  }

  processo_t* proc = *lista_processos;
  while (proc->prox != NULL) {
    proc = proc->prox;
  }
  proc->prox = processo;
  return processo;
}

processo_t* obter_processo_por_id(int id, processo_t* lista_processos) {
  if (lista_processos == NULL) {
    return NULL;
  }

  processo_t* processo = lista_processos;
  do {
    if (processo->id == id) {
      return processo;
    }
    processo = processo->prox;
  } while (processo != NULL);
  
  return NULL;
}

pagina_t* criar_pagina_processo(processo_t* processo, int numero, int quadro) {
  pagina_t* pagina = (pagina_t*) malloc(sizeof(pagina_t));
  pagina->numero = numero;
  pagina->quadro = quadro;

  if (processo->paginas == NULL) {
    processo->paginas = pagina;
    return pagina;
  }

  pagina_t* pag = processo->paginas;
  while (pag->prox != NULL) {
    pag = pag->prox;
  }
  pag->prox = pagina;
  return pagina;
}
