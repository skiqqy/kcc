/* TODO: Header */

#include <unistd.h>
#include<string.h>
#include<fcntl.h>

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