#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

int main()
{
    InitTerminalDriver();
    InitTerminal(1);

    while (1) {
        sleep(1);
    }

    exit(0);
}

