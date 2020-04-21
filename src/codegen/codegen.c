/* TODO: Header */

#include "codegen.h"
#include "registers.h"
#include "instr/stack.h"
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

/* Prototypes */
void writeAssembly(int, char*);

/* TODO: Given filename, opens, writes and closes */
void writeOut(char* filename, char* text)
{
	/* Open the file for reading */
	int fd = open(filename, O_CREAT);

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

	/* Check the instruction type */
	if(instruction->type == PUSH_R)
	{
		struct PushInstructionRegister* pushIR = (struct PushInstructionRegister*)instruction;

		/* Find the correct push instruction */
		char* pushInstructionString;
		if(pushIR->width == 1)
		{
			pushInstructionString = "pushb";
		}
		else if(pushIR->width == 2)
		{
			pushInstructionString = "pushw";
		}
		else if(pushIR->width == 4)
		{
			pushInstructionString = "pushl";
		}
		else if(pushIR->width == 8)
		{
			pushInstructionString = "pushq";
		}


		/* Get the register name */
		char* registerName = registerNames[pushIR->registerType];

		strcat(instructionString, pushInstructionString);
		strcat(instructionString, " ");
		strcat(instructionString, registerName);		
	}

	return instructionString;
}