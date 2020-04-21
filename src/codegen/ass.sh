# Assemble
gcc testcodegen.c -o codegenTest
./codegenTest
gcc out.s -m32 -o ./kcc.out
./kcc.out