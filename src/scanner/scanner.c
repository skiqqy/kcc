#include "tokens.h"
//#include "tst.h"
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
  if(debug > 0) printf("Adding Token: %s\n", rep);

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

int r_comp (regex_t* r, const char* expr)
{
  int err_code = regcomp (r, expr, REG_EXTENDED);
  if (err_code == 0) return 0;

  char err_msg[512];
  regerror (err_code, r, err_msg, 512);
  printf ("error compiling regex '%s': %s\n", expr, err_msg);
  return err_code;
}

int* r_gmatch (regex_t* r, regmatch_t* g, const char* str)
{
  int mnum = 0;
  int* matches;
  matches = (int*)malloc(sizeof(int));

  int gnum = r->re_nsub + 1;
  if(!regexec(r, str, (size_t) gnum, g, 0)){
    for (int i = 0; i < gnum; i++) {
      if (g[i].rm_so == (size_t)(-1) || g[i].rm_so == g[i].rm_eo || g[i].rm_so > strlen(str)) {}
      else {
        if(debug > 1) printf("%d (%d:%d), ", (int) i, g[i].rm_so, g[i].rm_eo);
        matches[mnum] = i-1;
        mnum++;
        matches = (int*)realloc(matches, (mnum+1) * sizeof(int));
      }
    }
  }
  if(debug > 1) printf("\n");
  
  matches[0] = mnum;
  return matches;
}

void tokenise(char* fname, Grammar* g) {
  regex_t r;
  int gnum;
  int* gm;

  FILE *file;
  char buffer[255];
  file = fopen(fname, "r");
  while(fscanf(file, "%255[^\n]\n", buffer) == 1) {
    if(debug > 0) printf("-------------\nReading line:\t%s\n", buffer);

    int mnum = 0;
    char tmpstr[strlen(buffer)];
    for(int i = 0; i < g->num; i++){
      r_comp(&r, g->st[i]->pat);
      gnum = r.re_nsub + 1;
      regmatch_t* grps = malloc(gnum * sizeof(regmatch_t));
      gm = r_gmatch(&r, grps, buffer);


      if(gm[0] > 2) {
        printf("\033[1;31mTHIS SHOULDN'T HAPPEN!\033[0;0m\n");
      } else if(gm[0] == 2) {
        strcpy(tmpstr, buffer);
        tmpstr[grps[gm[1]].rm_eo] = 0;
        if(mnum == 0) {
          printf("Matching token #%d %s >>> \033[1;32m%s\033[0;0m\n", i, g->st[i]->rep, tmpstr+grps[gm[1]].rm_so);
        }
        else {
          printf("Additional match #%d %s >>> \033[1;31m%s\033[0;0m\n", i, g->st[i]->rep, tmpstr+grps[gm[1]].rm_so);
        }
        mnum++;
      }
    }
    if(mnum > 1) printf("\033[1;31mAMBIGUOUS PATTERN!\033[0;0m\n");
    if(mnum == 0) printf("\033[1;33mNO MATCHES!\033[0;0m\n");
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
  while(fscanf(file, "%255[^\n]\n", buffer) == 1) {
    addToken(&ST, TRUE, buffer);
  }
  fclose(file);

  if(argv != 2) {
    printf("No arguments given.");
  } else {
    tokenise(argc[1], &ST);
  }

  return 0;
}
