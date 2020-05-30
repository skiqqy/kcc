#include "tokens.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<regex.h>

#define TRUE 1
#define FALSE 0

int debug = 1;
//THIS IS WORK IN PROGRESS, COMMENTS WILL HOPEFULLY FOLLOW SOON.

typedef struct {
  struct token** st; //array of pointers to tokens
  size_t all; //total allocated
  size_t num; //number of used space by tokens
  char* pattern; //regex consisting of all terminal tokens
} Grammar;

void initGrammar(Grammar* g) {
  MAIN.isTerm = TRUE;
  MAIN.rep = "main";

  g->st = (struct token**)malloc(16 * sizeof(struct token*));
  g->pattern = (char*)malloc(8 * sizeof(char));
  strcpy(g->pattern, "(^main)");
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
  g->pattern = (char*)realloc(g->pattern, (strlen(g->pattern)+strlen(rep)+5)*sizeof(char));
  if(debug > 0) printf("Adding Token: %s\n", rep);
  strcat(g->pattern, "|(^");
  strcat(g->pattern, rep);
  strcat(g->pattern, ")");
  strcpy(g->st[g->num]->rep, rep);
  g->num++;
}

int r_comp (regex_t* r, const char* expr)
{
  int err_code = regcomp (r, expr, REG_EXTENDED);
  if (err_code == 0) return 0;

  char err_msg[512];
  regerror (err_code, r, err_msg, 512);
  printf ("error compiling regex '%s': %s\n", expr, err_msg);
  return err_code;
}

int* r_gmatch (regex_t* r, const char* str)
{
  int mnum = 0;
  int* matches;
  matches = (int*)malloc(sizeof(int));

  int gnum = r->re_nsub + 1;
  regmatch_t *g = malloc(gnum * sizeof(regmatch_t));
  regexec(r, str, (size_t) gnum, g, 0);

  if(debug > 1) printf("len: %d >", (int)strlen(str));

  int i;
  for (i = 0; i < gnum; i++) {
    if (g[i].rm_so == (size_t)(-1) || g[i].rm_so == g[i].rm_eo || g[i].rm_so > strlen(str)) {}
    else {
      if(debug > 1) printf("%d (%d:%d), ", (int) i, g[i].rm_so, g[i].rm_eo);
      matches[mnum] = i-1;
      mnum++;
      matches = (int*)realloc(matches, (mnum+1) * sizeof(int));
    }
  }
  if(debug > 1) printf("\n");
  matches[0] = mnum;
  return matches;
}

void tokenise(char* fname, Grammar* g) {
  regex_t r;
  r_comp(&r, g->pattern);
  if(debug > 0) printf(">>Using RegEx: %s\n\n", g->pattern);

  FILE *file;
  char buffer[255];
  file = fopen(fname, "r");
  while(fscanf(file, "%s", buffer) == 1) {
    if(debug > 0) printf("-------------\nRead string:\t%s\n", buffer);
    int* gm = r_gmatch(&r, buffer);
    if(gm[0] > 2) {
      for(int i = 1; i < gm[0]; i++) {
        if(debug > 0) printf("Multiple matches\t\033[1;31m#%d\033[0;0m\n", gm[i]);
      }
    } else if(gm[0] == 2) {
        if(debug > 0) {
          if(gm[1] == g->num) printf("\033[1;36mNo token listed\033[0;0m\n");
          else printf("Exact match\t\033[1;32m#%d: %s\033[0;0m\n", gm[1], g->st[gm[1]]->rep);
        }
    } else {
        if(debug > 0) printf("\033[1;31mNo match\033[0;0m\n");
    }
    if(debug > 0) printf("-------------\n\n");

  }
  fclose(file);
  regfree(&r);
}

int main(int argv, char* argc[]){
  Grammar ST;
  initGrammar(&ST);

  //reading built-in terminals from file (pre-sorted, just to simplify things for the moment)
  FILE *file;
  char buffer[255];
  file = fopen("term", "r");
  while(fscanf(file, "%s\n", buffer) == 1) {
    addToken(&ST, TRUE, buffer);
  }
  fclose(file);

  //TODO: move this somewhere else
  //ST.pattern = (char*)realloc(ST.pattern, (strlen(ST.pattern)+6)*sizeof(char));
  //strcat(ST.pattern, "|(^.)");

  if(argv != 2) {
    printf("No arguments given.");
  } else {
    tokenise(argc[1], &ST);
  }

  return 0;
}
