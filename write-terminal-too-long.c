#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <assert.h>

void writer(void *);

char *string;
int length = 1055;

int main()
{
    InitTerminalDriver();
    InitTerminal(1);

    ThreadCreate(writer, NULL);

    ThreadWaitAll();

    exit(0);
}

void
writer(void *arg)
{
    int status;
    (void)arg;

    string = malloc(length * sizeof(char));
    for (int i = 0; i < length; i++) {
        string[i] = 'j';
    }

    printf("Doing WriteTerminal... \n");
    status = WriteTerminal(1, string, length);
    if (status != length) {
        printf("Status (%d) does not match length (%d)\n", status, length);
        return;
    }
    printf("Done: status = %d.\n", status);
}
