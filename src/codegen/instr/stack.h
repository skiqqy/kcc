/* All stack-related functions */

#include "../codegen.h"
#include "../registers.h"

/* A push instruction (immediate) */
struct PushInstructionImmediate
{
	enum InstructionType type;
	unsigned char width;
	char* value;
};

/* A push instruction (register) */
struct PushInstructionRegister
{
	enum InstructionType type;
	enum Register registerType;
};