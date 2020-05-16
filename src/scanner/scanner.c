#include "tokens.h"
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
  struct token** st; //array of pointers to tokens
  size_t all; //total allocated
  size_t num; //number of used space by tokens
} Grammar;

void initGrammar(Grammar* g) {
  MAIN.isTerm = TRUE;
  MAIN.rep = "main";

  g->st = (struct token**)malloc(16 * sizeof(struct token*));
  g->st[0] = &MAIN;
  g->num = 1;
  g->all = 16;
}

void addToken(Grammar* g, struct token* t) {
  if (g->num == g->all) {
    g->all *= 2;
    g->st = (struct token**)realloc(g->st, g->all * sizeof(struct token*));
  }
  g->st[g->num++] = t;
}

int main(){
  Grammar ST;
  
  return 0;
}
