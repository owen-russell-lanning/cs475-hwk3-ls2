#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"
#include "string.h"
#include <sys/stat.h>
#include <libgen.h>

/**
 * returns the number of slashes in a string
 */
int countSlash(char *s)
{
	int sLen = strlen(s);
	int slashes = 0;

	// get the amount of slashes
	for (int i = 0; i < sLen; i++)
	{
		char c = s[i];
		if (c == '/')
		{
			slashes++;
		}
		else
		{
		}
	}

	return slashes;
}

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char *argv[])
{
	// stack stores the lines to print out
	stack_t *s = initstack();

	if (argc <= 1)
	{ // no path
		printf("Not enough arguments given\n");
		return 0;
	}

	char *path = argv[1];

	char *searchFile;
	int searchForFile = 0; // whether or not search for a file
	if (argc >= 3)
	{
		searchForFile = 1;
		searchFile = argv[2];
	}

	// put first element onto stack
	push(s, path);
	while (s->size)
	{
		// count items in the folder
		stacknode_t *top = s->top;
		char *newPath = top->data;

		// check if path is a directory
		struct stat pathStat;
		stat(newPath, &pathStat);

		// get items in the folder and add to the stack
		pop(s);

		int slashes = countSlash(newPath) - 1; // remove one slash for first list
		char *baseN = basename(newPath);

		// print a tab for each slash
		for (int i = 0; i < slashes; i++)
		{
			printf("\t");
		}

		if (!S_ISDIR(pathStat.st_mode))
		{
			if (!searchForFile || !strcmp(searchFile, baseN))
			{
				// print the file name
				// get the file name from the full path
				printf("%s (%ld bytes)\n", baseN, pathStat.st_size);
				
			}
			continue;
		}

		if (strcmp(path, newPath))
		{

			// print the directory
			printf("%s/ (directory) \n", baseN);
		}

		int itemCount = countls2(newPath);

		int parentStrLen = strlen(newPath);

		// keep reading for ls2 until we run out of files
		for (int i = 0; i < itemCount; i++)
		{
			char *item = ls2(newPath, i);

			// clone string and apparent the parent directory to it
			int newStrLen = strlen(item) + parentStrLen + 1;
			char *cloneString = malloc(newStrLen);
			strcpy(cloneString, newPath);
			strcat(cloneString, "/");
			strcat(cloneString, item);
			cloneString[newStrLen] = '\0';

			push(s, cloneString);
		}
	}

	// free up stack
	freestack(s);
	return 0;
}
