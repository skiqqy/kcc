#include "tokens.h"
#include "rex.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

int debug = 1; //verbosity level

void tokenise(char* fname, Grammar* g) {
  struct gmatches gm;

  FILE *file;
  char buffer[255];
  file = fopen(fname, "r");
  while(fscanf(file, "%255[^\n]\n", buffer) == 1) {
    if(debug > 0) printf("-------------\nReading line:\t%s\n", buffer);

    int mnum = 0;
    char tmpstr[strlen(buffer)];
    for(int i = 0; i < g->num; i++){
      gm = r_gmatch(g->st[i]->pat, buffer);

      if(gm.m[0] > 2) {
        printf("\033[1;31mTHIS SHOULDN'T HAPPEN!\033[0;0m\n");
      } else if(gm.m[0] == 2) {
        if(mnum == 0) {
          printf("Matching token #%d %s >>> \033[1;32m%s\033[0;0m\n", i, g->st[i]->rep, gm.s[1]);
        }
        else {
          printf("Additional match #%d %s >>> \033[1;31m%s\033[0;0m\n", i, g->st[i]->rep, gm.s[1]);
        }
        mnum++;
      }
    }
    if(mnum > 1) printf("\033[1;31mAMBIGUOUS PATTERN!\033[0;0m\n");
    if(mnum == 0) printf("\033[1;33mNO MATCHES!\033[0;0m\n");
    if(debug > 0) printf("-------------\n\n");

  }
  fclose(file);
}

int main(int argv, char* argc[]){
  Grammar ST;
  initGrammar(&ST);

  FILE *file;
  char buffer[255];
  file = fopen("term", "r");
  while(fscanf(file, "%255[^\n]\n", buffer) == 1) {
    if(debug > 0) printf("Adding Token: %s\n", buffer);
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
