#include <assert.h>
#include <string.h>
#include <terminals.h>
#include <hardware.h>
#include <stdio.h>
#include <stdlib.h>
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
    int i;

    if (InitTerminalDriver() == ERROR)
        exit(1);

    for (i = 0; i < NUM_TERMINALS; i++) {
        if (InitTerminal(i) == ERROR)
            exit(1);
    }

    InitTerminal(1);

    struct termstat *stats =
        malloc(sizeof(struct termstat) * NUM_TERMINALS);

    if (stats == NULL)
        exit(1);

    int status = TerminalDriverStatistics(stats);
    assert(status == 0);

	for (i = 0; i < NUM_TERMINALS; i++) {
		struct termstat expected = {0, 0, 0, 0};
		assert(memcmp(&stats[i], &expected, sizeof(struct termstat)) == 0);
	}

    status = WriteTerminal(1, string1, length1);
    if (status != length1) {
        fprintf(stdout, "Did not write correct amount\n");
        exit(1);
    }

    sleep(1);

    status = TerminalDriverStatistics(stats);
    assert(status == 0);

    struct termstat expected = {0, length1 + 1, length1, 0};
    fprintf(stdout, "tty: %d, %d \t user: %d, %d\n",
        stats[1].tty_in, stats[1].tty_out, stats[1].user_in, stats[1].user_out);
    assert(memcmp(&stats[1], &expected, sizeof(struct termstat)) == 0);

    exit(0);
}
