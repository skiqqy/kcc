#include<stdio.h>
#include "codegen.c"
#include<stdlib.h>

int main()
{

	/* Create a push register instruction */
	struct GlobalPlacement testInstr4;
	testInstr4.type = GLOBAL_P;
	testInstr4.name = "main";
		
	char* instruction = generateAssemblyInstruction((struct Instruction*)&testInstr4);
	printf("Output instruction: \"%s\"\n", instruction);
	free(instruction);

	/* Create a push register instruction */
	struct SectionPlacement testInstr5;
	testInstr5.type = SECTION_P;
	testInstr5.name = "text";
		
	instruction = generateAssemblyInstruction((struct Instruction*)&testInstr5);
	printf("Output instruction: \"%s\"\n", instruction);
	free(instruction);


	
	


	/* Create a push register instruction */
	struct LabelPlacement testInstr3;
	testInstr3.type = LABEL_P;
	testInstr3.label = "main";
				
	instruction = generateAssemblyInstruction((struct Instruction*)&testInstr3);
	printf("Output instruction: \"%s\"\n", instruction);
	free(instruction);


	/* Create a push register instruction */
	struct PushInstructionRegister testInstr;
	testInstr.type = PUSH_R;
	testInstr.width = 4;
	testInstr.registerType = EAX;
		
	instruction = generateAssemblyInstruction((struct Instruction*)&testInstr);
	printf("Output instruction: \"%s\"\n", instruction);
	free(instruction);

	/* Create a push register instruction */
	struct PopInstruction testInstr2;
	testInstr2.type = POP_R;
	testInstr2.width = 4;
	testInstr2.registerType = EAX;
			
	instruction = generateAssemblyInstruction((struct Instruction*)&testInstr2);
	printf("Output instruction: \"%s\"\n", instruction);
	free(instruction);
	
		
			

}