#include<string.h>
#include<stdlib.h>

struct tst {
  struct tst* smaller;
  struct tst* equal;
  struct tst* greater;
  char c;
  int val;
};

void tst_insert(struct tst* node, char* str, int val, int pos) {
  if(pos == strlen(str)){
    node->val = val;
    return;
  }

  if(str[pos] > node->c){
    if(node->greater == NULL){
      node->greater = (struct tst*)malloc(sizeof(struct tst));
      node->greater->c = str[pos];
      node->greater->val = -1;
    }
    tst_insert(node->greater, str, val, pos);
  } else if(str[pos] < node->c){
    if(node->smaller == NULL){
      node->smaller = (struct tst*)malloc(sizeof(struct tst));
      node->smaller->c = str[pos];
      node->smaller->val = -1;
    }
    tst_insert(node->smaller, str, val, pos);
  } else if(node->c == str[pos]){
    if(node->equal == NULL){
      node->equal = (struct tst*)malloc(sizeof(struct tst));
      node->equal->c = str[pos];
      node->equal->val = -1;
    }
    tst_insert(node->equal, str, val, pos+1);
  }
}
void tst_ins(struct tst* root, char* str, int val) {
  tst_insert(root, str, val, 0);
}

struct tst* tst_init(){
  struct tst* root = (struct tst*)malloc(sizeof(struct tst));
  root->c = ' ';
  root->val = -1;
  return root;
}

int tst_f(struct tst* node, char* str, int pos){
  if(node == NULL) return -2; 
  if(pos == strlen(str)) return node->val;
  if(str[pos] == node->c) return tst_f(node->equal, str, pos+1);
  if(str[pos] > node->c) return tst_f(node->greater, str, pos);
  if(str[pos] < node->c) return tst_f(node->smaller, str, pos);
}
int tst_find(struct tst* node, char* str){
  tst_f(node, str, 0);
}
