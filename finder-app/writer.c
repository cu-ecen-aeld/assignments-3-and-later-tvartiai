
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#define FILE_NAME_INDEX 1
#define STRING_INDEX    2

int main(int argc, char *argv[])
{
    int ret = 0;

    setlogmask (LOG_UPTO (LOG_DEBUG));
    openlog ("writer", LOG_CONS | LOG_NDELAY, LOG_USER);
    syslog (LOG_DEBUG, "Writing %s to %s", argv[STRING_INDEX], argv[FILE_NAME_INDEX]);

    if (3 != argc )
    {
        printf("Wrong number of arguments. Please give <input text> and <filename> as arguments.\n");
        syslog (LOG_ERR, "Invalid argument count, expected 3 got %d.", argc);
        ret = 1;
    }
    else
    {
        FILE *pFile = fopen(argv[FILE_NAME_INDEX],"w");

        if(pFile == NULL)
        {
            printf("File open failed.\n");
            syslog (LOG_ERR, "Opening file %s for writing failed.", argv[FILE_NAME_INDEX]);
            ret = 1;
        }
        else
        {
            printf("File opened for writing.\n");
            fprintf(pFile,"%s", argv[STRING_INDEX]);
            fclose(pFile);
        }
    }

    closelog ();

    return ret;
}
