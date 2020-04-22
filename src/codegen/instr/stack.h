/* All stack-related functions */

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
	unsigned char width;
	enum Register registerType;
};

/* A pop instruction */
struct PopInstruction
{
	enum InstructionType type;
	unsigned char width;
	enum Register registerType;
};