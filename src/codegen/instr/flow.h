/* All flow-related functions */

/* A jump instruction (immediate) */
struct JumpImmediateInstruction
{
	enum InstructionType type;
	char* label;
};

/* TODO: A jump instruction (register) */
struct JumpRegisterInstruction
{
	enum InstructionType type;
	char* label;
};