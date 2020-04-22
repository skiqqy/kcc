/* Represents the type of instruction */
enum InstructionType
{
	PUSH_I, PUSH_R, POP_R,






	LABEL_P, SECTION_P, GLOBAL_P,


	JUMP_I,








	NOP,

	MOVEIR, MOVEIRD
	JUMP_I
};

/* Represents an instruction */
struct Instruction
{
	enum InstructionType type;
};