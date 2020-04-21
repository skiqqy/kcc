/* Represents the type of instruction */
enum InstructionType
{
	PUSH_I, PUSH_R, POP_R
};

/* Represents an instruction */
struct Instruction
{
	enum InstructionType type;
};