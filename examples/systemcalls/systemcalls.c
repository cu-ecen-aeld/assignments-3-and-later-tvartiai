#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "systemcalls.h"

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    bool ret_value = true;

    if (-1 == system(cmd))
        ret_value = false;

    return ret_value;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    pid_t pid;
    bool ret_value = false;

    int i, status;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    fflush(stdout);

    pid = fork();
    switch (pid) {
        case -1:
            printf("DO_EXEC: Fork failed\n");
            return false;
        case 0:
            printf("Child executing\n");
            exit (execv(command[0], command));
        default:
            printf("Child is PID %d\n", (int) pid);
            wait(&status);
    }

    va_end(args);

    if (0 == WEXITSTATUS(status))
    {
        ret_value = true;
    }

    return ret_value;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i, status;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    int kidpid;
    int fd = open( outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if (fd < 0)
    {
        printf("REDIRECT: File open failed.\n");
        return false;
    }
    switch (kidpid = fork())
    {
    case -1:
        perror("fork");
        return false;
    case 0:
        if (dup2(fd, 1) < 0) {
            perror("dup2");
            return false;
        }
        exit(execv(command[0], command));
        close(fd);
    default:
        wait(&status);
        close(fd);
    }

    va_end(args);
    return WEXITSTATUS(status);
}
