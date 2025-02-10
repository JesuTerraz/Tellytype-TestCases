#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <assert.h>

void reader(void *);

int length = 5;

int main()
{
    InitTerminalDriver();
    InitTerminal(1);

    for (int i = 0; i < 5; i++) {
        ThreadCreate(reader, NULL);
    }

    ThreadWaitAll();

    exit(0);
}

void
reader(void *arg)
{
    int status;
    (void)arg;

    char str[length];

    status = ReadTerminal(1, str, length);
    if (status <= 0) {
        printf("Nothing was read! (%d)\n", status);
        return;
    }

    // if (str[status - 1] == '\0') printf("Term found!\n");

    printf("Done: status = %d: ", status);
    for (int i = 0; i < status; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}
