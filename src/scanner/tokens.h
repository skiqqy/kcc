#define OCB 0     //opening curly brace
#define CCB 1     //closing curly brace
#define ORB 2     //opening round bracket
#define CRB 3     //closing round bracket
#define SCL 4     //semicolon
#define INT 5     //int
#define DBL 6     //double
#define CHA 7     //char
#define PLS 8     //plus
#define MIN 9     //minus
#define TIM 10    //times
#define DIV 11    //divide/slash
#define CMT 12    //comment (//)
#define OCM 13    //opening comment (/*)
#define CCM 14    //closing comment (*/)

struct atoms {
  //this structure will represent a symbol table containing all the important
  //infos about attributes of the terminal tokens
};

struct grammar {
  //this structure will represent a symbol table containing syntax related
  //information, i.e. a list of non-terminals
};

struct terminal {
  int id; //unique id for every terminal
  struct atoms* attr; //pointer to the symbol table containing info about token
};

struct nonterminal {
  int id; //unique id for every non terminal
  struct grammer* attr;//pointer to the symbol table containung info about token
};
