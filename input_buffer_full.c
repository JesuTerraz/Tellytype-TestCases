#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>
#include <assert.h>
#include "read_buf.c"

int main()
{
    InitTerminalDriver();
    InitTerminal(1);

    printf("WARNING: Make sure MAX_BUFLEN is small. 10 seconds");
    printf(" before ReadTerminal is called don't type any new lines.\n");

    sleep(10);

    char *str = malloc(20 * sizeof(char));
    int status = ReadTerminal(1, str, 20);
    assert (status > 0);

    print_buf(str, status);

    exit(0);
}

