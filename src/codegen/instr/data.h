/* All data movement related instructions */

/* A mov immediate->register */
struct MoveIRInstruction
{
	enum InstructionType type;
	unsigned char width;
	char* value;
	enum Register registerType;	
};

/* A mov immediate->register (deref) */
struct MoveIRDInstruction
{
	enum InstructionType type;
	unsigned char width;
	char* value;
	enum Register registerType;	
};