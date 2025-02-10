#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void writer1(void *);
void writer2(void *);

char string1[] = "abcdefghijklmnopqrstuvwxyz\n";
int length1 = sizeof(string1) - 1;

char string2[] = "0123456789\n";
int length2 = sizeof(string2) - 1;

int
main()
{
    InitTerminalDriver();
    InitTerminal(1);

    for (int i = 0; i < 4; i++) {
        ThreadCreate(writer1, NULL);
        ThreadCreate(writer2, NULL);
    }

    ThreadWaitAll();
    while(1) sleep(10);

    exit(0);
}

void
writer1(void *arg)
{
    int status;
    (void)arg;

    status = WriteTerminal(1, string1, length1);
    if (status != length1)
	fprintf(stderr, "Error: writer1 status = %d, length1 = %d\n",
	    status, length1);
}

void
writer2(void *arg)
{
    int status;
    (void)arg;

    status = WriteTerminal(1, string2, length2);
    if (status != length2)
	fprintf(stderr, "Error: writer2 status = %d, length2 = %d\n",
	    status, length2);
}
