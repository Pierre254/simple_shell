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

typedef struct ListNode {
    int num;
    char *str;
    struct ListNode *next;
} ListNode;

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

typedef struct BuiltinCommand {
    char *type;
    int (*func)(CommandInfo *);
} BuiltinCommand;

int shellLoop(char **args);
int findBuiltin(CommandInfo *cmdInfo);
void findCommand(CommandInfo *cmdInfo);
void forkCommand(CommandInfo *cmdInfo);

int isCommand(CommandInfo *cmdInfo, char *cmd);
char *duplicateChars(char *str, int start, int end);
char *findPath(CommandInfo *cmdInfo, char *cmd, char *envPath);

void errorOutput(char *message);
int writeOutput(char *str, int fd);
int printOutput(char *str, int fd);

int strLength(char *str);
int strCompare(char *str1, char *str2);
char *startsWith(const char *str, const char *prefix);
char *concatenateStrings(char *str1, char *str2);

char *copyString(char *dest, char *src);
char *duplicateString(const char *str);
void printString(char *str);
int printChar(char character);

char *copySubstring(char *dest, char *src, int length);
char *concatenateSubstring(char *dest, char *src, int length);
char *findCharacter(char *str, char character);

char **tokenizeString(char *str, char *delimiter);
char **tokenizeString2(char *str, char delimiter);

char *memSet(char *block, char value, unsigned int size);
void freeMemory(char **ptr);
void *resizeMemory(void *ptr, unsigned int oldSize, unsigned int newSize);

int freeBlock(void **block);

int interpretInteractive(CommandInfo *cmdInfo);
int isDelimiter(char character, char *delimiters);
int isAlphabetic(int character);
int convertToInteger(char *str);

int parseIntError(char *str);
void displayError(CommandInfo *cmdInfo, char *message);
int printDecimal(int number, int fd);
char *convertNumber(long int value, int lowercase, int unsignedFlag);
void removeComments(char *str);

int exitShell(CommandInfo *cmdInfo);
int changeDirectory(CommandInfo *cmdInfo);
int displayHelp(CommandInfo *cmdInfo);

int displayHistory(CommandInfo *cmdInfo);
int manageAlias(CommandInfo *cmdInfo);

ssize_t getInput(CommandInfo *cmdInfo);
int getLineInput(CommandInfo *cmdInfo, char **buffer, size_t *size);
void handleInterruptSignal(int signal);

void clearCommandInfo(CommandInfo *cmdInfo);
void setCommandInfo(CommandInfo *cmdInfo, char **args);
void freeCommandInfo(CommandInfo *cmdInfo, int flag);

int isCommandChain(CommandInfo *cmdInfo, char *input, size_t *index);
void checkCommandChain(CommandInfo *cmdInfo, char *input, size_t *index, size_t length, size_t max);

int replaceAlias(CommandInfo *cmdInfo);
int replaceVariables(CommandInfo *cmdInfo);
int replaceString(char **str, char *replacement);

#endif

Main.c

#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info[] = {INFO_INIT};
    int fd = 2;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    populate_env_list(info);
    read_history(info);
    hsh(info, av);

    return EXIT_SUCCESS;
}
