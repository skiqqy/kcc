#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define TRUE 1
#define FALSE 0


struct token {
  int isTerm; //is the token a terminal? either 0 or 1
  char* rep; //string representation (if it is a terminal)
  char* pat; //string representation (if it is a terminal)
  int id; //id of the token (equal to regex group positon in pattern)
  struct token** var; //variations (if it is a non-terminal)
} MAIN;

typedef struct {
  struct token** st; //array of pointers to tokens
  size_t all; //total allocated
  size_t num; //number of used space by tokens
} Grammar;

void initGrammar(Grammar* g) {
  MAIN.isTerm = TRUE;
  MAIN.rep = "main";
  MAIN.pat = "(^\\s*main)";

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
  g->st[g->num]->id = g->num;
  g->st[g->num]->rep = (char*)malloc(sizeof(rep));
  g->st[g->num]->pat = (char*)malloc(sizeof(rep)+6*sizeof(char));

  strcpy(g->st[g->num]->rep, rep);
  strcpy(g->st[g->num]->pat, "(^\\s*");
  strcat(g->st[g->num]->pat, rep);
  strcat(g->st[g->num]->pat, ")");
  g->num++;
}
