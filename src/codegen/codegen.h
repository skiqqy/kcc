/* Represents the type of instruction */
enum InstructionType
{
	PUSH_I, PUSH_R
};

/* Represents an instruction */
struct Instruction
{
	enum InstructionType type;
};