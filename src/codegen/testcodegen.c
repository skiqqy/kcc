#include<stdio.h>
#include "codegen.c"
#include<stdlib.h>

int main()
{
	/* Create a push register instruction */
	struct PushInstructionRegister testInstr;
	testInstr.type = PUSH_R;
	testInstr.width = 4;
	testInstr.registerType = EAX;
		
	char* instruction = generateAssemblyInstruction((struct Instruction*)&testInstr);
	printf("Output instruction: \"%s\"", instruction);
	free(instruction);

	/* Create a push register instruction */
	struct PopInstruction testInstr2;
	testInstr2.type = POP_R;
	testInstr2.width = 4;
	testInstr2.registerType = EAX;
		
	instruction = generateAssemblyInstruction((struct Instruction*)&testInstr2);
	printf("Output instruction: \"%s\"", instruction);
	free(instruction);

}