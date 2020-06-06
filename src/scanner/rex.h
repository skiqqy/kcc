#include<regex.h>

struct gmatches{
  int* m; //[0] is number of group matches, following are group indices
  char** s;//array of matching strings
};

int r_comp (regex_t* r, const char* expr)
{
  int err_code = regcomp (r, expr, REG_EXTENDED);
  if (err_code == 0) return 0;

  char err_msg[512];
  regerror (err_code, r, err_msg, 512);
  printf ("error compiling regex '%s': %s\n", expr, err_msg);
  return err_code;
}

struct gmatches r_gmatch (char* pat, const char* str)
{
  regex_t r;
  r_comp(&r, pat);

  int mnum = 0;
  struct gmatches gm;
  gm.m = (int*)malloc(sizeof(int));
  gm.s = (char**)malloc(sizeof(char*));
  char tmpstr[strlen(str)];
  int gnum = r.re_nsub + 1;
  regmatch_t* grps = malloc(gnum * sizeof(regmatch_t));

  if(!regexec(&r, str, (size_t) gnum, grps, 0)){
    for (int i = 0; i < gnum; i++) {
      if (grps[i].rm_so == (size_t)(-1) || grps[i].rm_so == grps[i].rm_eo || grps[i].rm_so > strlen(str)) {}
      else {
        gm.m = (int*)realloc(gm.m, (mnum+1) * sizeof(int));
        gm.s = (char**)realloc(gm.s, (mnum+1) * sizeof(char*));

        strcpy(tmpstr, str);
        tmpstr[grps[i].rm_eo] = 0;

        gm.m[mnum] = i-1;
        gm.s[mnum] = (char*)malloc(strlen(tmpstr+grps[i].rm_so)*sizeof(char));
        strcpy(gm.s[mnum], tmpstr+grps[i].rm_so);
        mnum++;
      }
    }
  }
  
  gm.m[0] = mnum;
  regfree(&r);
  return gm;
}
