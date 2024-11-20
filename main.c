#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "processo.h"

int tam_mem_fisica;
int tam_pagina_quadro;
int tam_max_processo;
int qtd_quadros;
int qtd_quadros_livres;

processo_t* lista_processos;

int obter_configuracoes() {
  printf("Informe o tamanho da memória física: ");
  scanf("%d", &tam_mem_fisica);

  do {
    printf("Informe o tamanho da página/quadro: ");
    scanf("%d", &tam_pagina_quadro);
    if (tam_pagina_quadro <= tam_mem_fisica) {
      break;
    }
    printf("O tamanho da página não pode ser maior que o tamanho da memória física!\n");
  } while (1);

  do {
    printf("Informe o tamanho máximo dos processos: ");
    scanf("%d", &tam_max_processo);
    if (tam_max_processo <= tam_mem_fisica) {
      break;
    }
    printf("O tamanho máximo dos processos não pode ser maior que o tamanho da memória física!\n");
  } while (1);

  qtd_quadros = tam_mem_fisica / tam_pagina_quadro;
  printf("\n--- Memória física: %d - Página/Quadro: %d - Máx. processo: %d ---\n", tam_mem_fisica, tam_pagina_quadro, tam_max_processo);

  return 0;
}

int visualizar_memoria(int mem_fisica[]) {
  int percentual_disponivel = ((float)qtd_quadros_livres / (float)qtd_quadros) * 100;
  printf("Percentual de memória livre: %d%%\n", percentual_disponivel);
  int i;
  for (i = 0; i < qtd_quadros; i++) {
    printf("Valor no quadro %d: %d\n", i, mem_fisica[i]);
  }
  return 0;
}

int obter_quadro_livre(int mapa_quadros_livres[]) {
  while (1) {
    int quadro = rand() % qtd_quadros;
    if (!mapa_quadros_livres[quadro]) {
      return quadro;
    }
  }
}

int criar_processo(int mem_fisica[], int mapa_quadros_livres[]) {
  int id_processo;
  int tam_processo;

  do {
    printf("Informe um número para identificar o processo: ");
    scanf("%d", &id_processo);
    if (id_processo < 0) {
      printf("O identificador do processo deve ser um inteiro maior ou igual a 0!\n");
      continue;
    }
    if (obter_processo_por_id(id_processo, lista_processos) != NULL) {
      printf("Já existe um processo com esse ID!\n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("Informe o tamanho do processo: ");
    scanf("%d", &tam_processo);
    if (tam_processo <= tam_max_processo) {
      break;
    }
    printf("O tamanho do processo não pode ser maior que o máximo (máximo: %d)!\n", tam_max_processo);
  } while (1);

  int qtd_paginas = ceil((float)tam_processo / (float)tam_pagina_quadro);
  if (qtd_paginas > qtd_quadros_livres) {
    printf("Não há memória suficiente para alocar o processo...");
    return 0;
  }

  processo_t* processo = criar_e_inserir_processo(id_processo, tam_processo, qtd_paginas, &lista_processos);

  int i;
  for (i = 0; i < qtd_paginas; i++) {
    int quadro = obter_quadro_livre(mapa_quadros_livres);
    mem_fisica[quadro] = id_processo;
    mapa_quadros_livres[quadro] = 1;
    qtd_quadros_livres -= 1;
    criar_pagina_processo(processo, i, quadro);
  }

  printf("Processo criado!\n");
  return 0;
}

int visualizar_tabela_paginas() {
  int id_processo;
  printf("Informe o número do processo: ");
  scanf("%d", &id_processo);

  processo_t* processo = obter_processo_por_id(id_processo, lista_processos);

  if (processo == NULL) {
    printf("Processo não encontrado...\n");
    return 0;
  }

  printf("ID do processo: %d\n", processo->id);
  printf("Tamanho do processo: %d\n", processo->tamanho);

  printf("--- Tabela de páginas ---\n");
  pagina_t* pagina = processo->paginas;
  while (pagina != NULL) {
    printf("Página %d - Quadro %d\n", pagina->numero, pagina->quadro);
    pagina = pagina->prox;
  }
  printf("-------------------------\n");

  return 0;
}

int main() {
  obter_configuracoes();
  int mem_fisica[qtd_quadros];
  int mapa_quadros_livres[qtd_quadros];
  qtd_quadros_livres = qtd_quadros;
  int i;
  for (i = 0; i < qtd_quadros; i++) {
    mem_fisica[i] = -1;
    mapa_quadros_livres[i] = 0;
  }

  int opcao;
  while (1) {
    printf("\n");
    printf("--------------------------------\n");
    printf("1 - Visualizar memória\n");
    printf("2 - Criar processo\n");
    printf("3 - Visualizar tabela de páginas\n");
    printf("4 - Sair\n");
    printf("--------------------------------\n");
    printf("Seleciona uma opção: ");
    scanf("%d", &opcao);
    printf("\n");
  
    if (opcao < 1 || opcao > 4) {
      printf("Informe uma opção válida\n");
      continue;
    }

    switch (opcao) {
      case 1: visualizar_memoria(mem_fisica);
              break;
      case 2: criar_processo(mem_fisica, mapa_quadros_livres);
              break;
      case 3: visualizar_tabela_paginas();
              break;
      case 4: return 0;
      default: break;
    }
  }

  return 0;
}
