#include<stdio.h>
#include "codegen.c"

int main()
{
	/* Create a push register instruction */
	struct PushInstructionRegister testInstr;
	testInstr.type = PUSH_R;
	testInstr.width = 2;
	testInstr.registerType = EAX;
	
	
	char* instruction = generateAssemblyInstruction(&testInstr);
	printf("Output instruction: \"%s\"", instruction);
}