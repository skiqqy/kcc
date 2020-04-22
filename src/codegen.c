/* TODO: Header */

#include "codegen.h"
#include "codegen/registers.h"
#include "codegen/instr/stack.h"
#include "codegen/instr/asm.h"
#include "codegen/instr/flow.h"
#include "codegen/instr/misc.h"
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

/* Prototypes */
void writeAssembly(int, char*);

/* TODO: Given filename, opens, writes and closes */
void writeOut(char* filename, char* text)
{
	/* Open the file for reading */
	signed long fd = open(filename, O_CREAT|O_RDWR, S_IRWXU);
	printf("fd: %d\n", (signed int)fd);

	/* Check to make sure we have a valid fd */
	if(fd >= 0)
	{
		/* Write to the file */
		writeAssembly(fd, text);

		/* Close the file */
		close(fd);
	}
	else
	{
		/* TODO: Error handling, error opening file */
	}
}


/**
 * Write the generated assembly string
 * out to the file specified by the
 * descriptor `fd`.
 */
void writeAssembly(int fd, char* text)
{
	/* Get the length of the text */
	unsigned long textLength = strlen(text);

	/* Write the bytes to the file, `fd` */
	write(fd, text, textLength);
}

/* Transformation function (Instruction) -> (char* [assembly text]) */
char* generateAssemblyInstruction(struct Instruction* instruction)
{
	/* The generated string */
	char* instructionString = NULL;

	/* TODO: By dynamic, more so than allocating 20 */
	instructionString = (char*)malloc(20);
	*instructionString = 0; /* Zero out the first byte, as to make empty string */

	/* Check the instruction type */
	if(instruction->type == PUSH_R)
	{
		struct PushInstructionRegister* pushIR = (struct PushInstructionRegister*)instruction;

		/* Find the correct push instruction */
		unsigned char width = pushIR->width;
		char* pushInstructionString;
		if(width == 1)
		{
			pushInstructionString = "pushb";
		}
		else if(width == 2)
		{
			pushInstructionString = "pushw";
		}
		else if(width == 4)
		{
			pushInstructionString = "pushl";
		}
		else if(width == 8)
		{
			pushInstructionString = "pushq";
		}

		/* Get the register name */
		char* registerName = registerNames[pushIR->registerType];

		/* Build the instruction string */
		strcat(instructionString, pushInstructionString);
		strcat(instructionString, " ");
		strcat(instructionString, registerName);		
	}
	else if(instruction->type == POP_R)
	{
		struct PopInstruction* popI = (struct PopInstruction*)instruction;

		/* Find the correct pop instruction */
		unsigned char width = popI->width;
		char* popInstructionString;
		if(width == 1)
		{
			popInstructionString = "popb";
		}
		else if(width == 2)
		{
			popInstructionString = "popw";
		}
		else if(width == 4)
		{
			popInstructionString = "popl";
		}
		else if(width == 8)
		{
			popInstructionString = "popq";
		}

		/* Get the register name */
		char* registerName = registerNames[popI->registerType];
		
		/* Build the instruction string */
		strcat(instructionString, popInstructionString);
		strcat(instructionString, " ");
		strcat(instructionString, registerName);		
	}
	else if(instruction->type == LABEL_P)
	{
		struct LabelPlacement* labelPI = (struct LabelPlacement*)instruction;

		/* Get the name of the label */
		char* labelName = labelPI->label;

		/* Build the instruction string */
		strcat(instructionString, labelName);
		strcat(instructionString, ":");
	}
	else if(instruction->type == SECTION_P)
	{
		struct SectionPlacement* sectionPI = (struct SectionPlacement*)instruction;

		/* Get the name of the section */
		char* sectionName = sectionPI->name;

		/* Build the instruction string */
		strcat(instructionString, ".");
		strcat(instructionString, sectionName);
	}
	else if(instruction->type == GLOBAL_P)
	{
		struct GlobalPlacement* globalPI = (struct GlobalPlacement*)instruction;

		/* Get the name of the globalized entity */
		char* globalName = globalPI->name;

		/* Build the instruction string */
		strcat(instructionString, ".global ");
		strcat(instructionString, globalName);
	}
	else if(instruction->type == JUMP_I)
	{
		struct JumpImmediateInstruction* jumpII = (struct JumpImmediateInstruction*)instruction;

		/* Get the label (or value TODO: rename) */
		char* label = jumpII->label;

		/* Build the instruction string */
		strcat(instructionString, "jmp ");
		strcat(instructionString, label);
	}
	else if(instruction->type == NOP)
	{
		/* Build the instruction string */
		strcat(instructionString, "nop");
	}
	else if(instruction->type == MOVEIR)
	{
		/* TODO: Implement me (Tristan) */
	}
	else if(instruction->type == MOVEIRD)
	{
		/* TODO: Implement me (Tristan) */
	}

	return instructionString;
}