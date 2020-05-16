#include "tokens.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

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

void addToken(Grammar* g, int isTerm, char* rep) {
  if (g->num == g->all) {
    g->all *= 2;
    g->st = (struct token**)realloc(g->st, g->all * sizeof(struct token*));
  }
  g->st[g->num] = (struct token*)malloc(sizeof(struct token));
  g->st[g->num]->isTerm = isTerm;
  g->st[g->num]->rep = (char*)malloc(sizeof(rep));
  strcpy(g->st[g->num]->rep, rep);
  g->num++;
}

int main(){
  Grammar ST;
  initGrammar(&ST);

  //reading built-in terminals from file
  FILE *file;
  char buffer[255];
  file = fopen("term", "r");
  while(fscanf(file, "%s\n", buffer) == 1) {
    addToken(&ST, TRUE, buffer);
  }
  fclose(file);

  for(int i=0; i<ST.num; i++){
    printf("%d: %s\n", i, ST.st[i]->rep);
  }
  
  return 0;
}
