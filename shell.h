#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/** A struct to represent a linked list node */
typedef struct ListNode {
	int num;
	char *str;
	struct ListNode *next;
} ListNode;

/** A struct to store information about a command */
typedef struct CommandInfo {
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	ListNode *env;
	ListNode *history;
	ListNode *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} CommandInfo;

/** A struct to represent a builtin command */
typedef struct BuiltinCommand {
	char *type;
	int (*func)(CommandInfo *);
} BuiltinCommand;

/* Define the shell_t type as an alias for struct shell */
typedef struct shell shell_t;

/** A struct to represent a shell instance */
struct shell {
	/* Add the fields that you need for your shell_t type */
	/* For example, you can have a pointer to a CommandInfo struct */
	CommandInfo *cmdInfo;
	/* You can also have other fields, such as flags, counters, etc. */
	int exit_flag;
	int error_count;
};

/* Declare the function that loops and interprets commands */
int shellLoop(char **args);

/* Declare the function that finds and executes a builtin command */
int findBuiltin(CommandInfo *cmdInfo);

/* Declare the function that finds and executes a regular command */
void findCommand(CommandInfo *cmdInfo);

/* Declare the function that forks and executes a command */
void forkCommand(CommandInfo *cmdInfo);

/* Declare the function that checks if a string is a command */
int isCommand(CommandInfo *cmdInfo, char *cmd);

/* Declare the function that duplicates a substring of characters */
char *duplicateChars(char *str, int start, int end);

/* Declare the function that finds the path of a command */
char *findPath(CommandInfo *cmdInfo, char *cmd, char *envPath);

/* Declare the function that outputs an error message */
void errorOutput(char *message);

/* Declare the function that writes a string to a file descriptor */
int writeOutput(char *str, int fd);

/* Declare the function that prints a string to a file descriptor */
int printOutput(char *str, int fd);

/* Declare the function that returns the length of a string */
int strLength(char *str);

/* Declare the function that compares two strings */
int strCompare(char *str1, char *str2);

/* Declare the function that checks if a string starts with a prefix */
char *startsWith(const char *str, const char *prefix);

/* Declare the function that concatenates two strings */
char *concatenateStrings(char *str1, char *str2);

/* Declare the function that copies a string to another string */
char *copyString(char *dest, char *src);

/* Declare the function that duplicates a string */
char *duplicateString(const char *str);

/* Declare the function that prints a string to stdout */
void printString(char *str);

/* Declare the function that prints a character to stdout */
int printChar(char character);

/* Declare the function that copies a substring to another string */
char *copySubstring(char *dest, char *src, int length);

/* Declare the function that concatenates a substring to another string */
char *concatenateSubstring(char *dest, char *src, int length);

/* Declare the function that finds a character in a string */
char *findCharacter(char *str, char character);

/* Declare the function that tokenizes a string using a delimiter */
char **tokenizeString(char *str, char *delimiter);

/* Declare the function that tokenizes a string using a single character delimiter */
char **tokenizeString2(char *str, char delimiter);

/* Declare the function that sets a block of memory to a value */
char *memSet(char *block, char value, unsigned int size);

/* Declare the function that frees a block of memory */
void freeMemory(char **ptr);

/* Declare the function that resizes a block of memory */
void *resizeMemory(void *ptr, unsigned int oldSize, unsigned int newSize);

/* Declare the function that frees a block of memory and sets it to NULL */
int freeBlock(void **block);

/* Declare the function that interprets commands in interactive mode */
int interpretInteractive(CommandInfo *cmdInfo);

/* Declare the function that checks if a character is a delimiter */
int isDelimiter(char character, char *delimiters);

/* Declare the function that checks if a character is alphabetic */
int isAlphabetic(int character);

/* Declare the function that converts a string to an integer */
int convertToInteger(char *str);

/* Declare the function that parses an integer and handles errors */
int parseIntError(char *str);

/* Declare the function that displays an error message with command info */
void displayError(CommandInfo *cmdInfo, char *message);

/* Declare the function that prints a decimal number to a file descriptor */
int printDecimal(int number, int fd);

/* Declare the function that converts a number to a string */
char *convertNumber(long int value, int lowercase, int unsignedFlag);

/* Declare the function that removes comments from a string */
void removeComments(char *str);

/* Declare the function that exits the shell */
int exitShell(CommandInfo *cmdInfo);

/* Declare the function that changes the current directory */
int changeDirectory(CommandInfo *cmdInfo);

/* Declare the function that displays the help message */
int displayHelp(CommandInfo *cmdInfo);

/* Declare the function that displays the history list */
int displayHistory(CommandInfo *cmdInfo);

/* Declare the function that manages the alias list */
int manageAlias(CommandInfo *cmdInfo);

/* Declare the function that gets the input from stdin */
ssize_t getInput(CommandInfo *cmdInfo);

/* Declare the function that gets the input from a file */
int getLineInput(CommandInfo *cmdInfo, char **buffer, size_t *size);

/* Declare the function that handles the interrupt signal */
void handleInterruptSignal(int signal);

/* Declare the function that clears the command info */
void clearCommandInfo(CommandInfo *cmdInfo);

/* Declare the function that sets the command info */
void setCommandInfo(CommandInfo *cmdInfo, char **args);

/* Declare the function that frees the command info */
void freeCommandInfo(CommandInfo *cmdInfo, int flag);

/* Declare the function that checks if a command is a chain */
int isCommandChain(CommandInfo *cmdInfo, char *input, size_t *index);

/* Declare the function that checks the type of a command chain */
void checkCommandChain(CommandInfo *cmdInfo, char *input, size_t *index, size_t length, size_t max);

/* Declare the function that replaces aliases in a command */
int replaceAlias(CommandInfo *cmdInfo);

/* Declare the function that replaces variables in a command */
int replaceVariables(CommandInfo *cmdInfo);

/* Declare the function that replaces a string with another string */
int replaceString(char **str, char *replacement);

#endif /* SIMPLE_SHELL_H */
