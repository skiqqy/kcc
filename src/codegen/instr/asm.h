struct LabelPlacement
{
	enum InstructionType type;
	char* label;
};

struct SectionPlacement
{
	enum InstructionType type;
	char* name;
};

struct GlobalPlacement
{
	enum InstructionType type;
	char* name;
};