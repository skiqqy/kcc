struct token {
  int isTerm; //is the token a terminal? either 0 or 1
  char* rep; //string representation (if it is a terminal)
  struct token** var; //variations (if it is a non-terminal)
} MAIN;
