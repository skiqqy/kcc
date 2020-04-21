Code generation
===============

The idea behind Kcc's code generation is that the parser will call emit
function(s) to apppend to a linked list of code objects. Once this process
is completed, the code-generation backend will traverse this list and
write to a file the assembly they represent. After this, gcc's assembler
will be called.