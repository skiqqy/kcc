#include<stdio.h>
#include "codegen.c"
#include<stdlib.h>

int main()
{
	/* Create a push register instruction */
	struct PushInstructionRegister testInstr;
	testInstr.type = PUSH_R;
	testInstr.width = 2;
	testInstr.registerType = EAX;
		
	char* instruction = generateAssemblyInstruction((struct Instruction*)&testInstr);
	printf("Output instruction: \"%s\"", instruction);
	free(instruction);
}