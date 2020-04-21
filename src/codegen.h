
/* Represents the type of instruction */
enum InstructionType
{
	PUSHB_I, PUSHW_I, PUSHL_I, PUSHQ_I	
};

/* Represents an instruction */
struct Instruction
{
	enum InstructionType type;
};

/* A push instruction (immediate) */
struct PushInstructionImmediate
{
	enum InstructionType type;
	unsigned char width;
	char* value;
};