/*
 * ============================================================================
 *
 *       Filename:  hail.c
 *    Description:  Extract lines x to y
 *        License:  GPLv3+
 *         Author:  Kevin Murray, spam@kdmurray.id.au
 *
 * ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


/* Defined as a macro to allow use of argv[0]. */
#define usage()                                                             \
        fprintf(stderr, "USAGE: %s <first>-<last> [<first>-<last ...]\n",   \
                argv[0])

int
main(int argc, const char **argv)
{
    FILE *fp = stdin;
    char *buf = NULL;
    size_t len = 0;
    ssize_t res = 0;
    size_t lineno = 0;
    size_t first, last;
    int i = 0;

    /* We expect to have at least one pair of start-finish line nums. */
    if (argc < 2) {
        usage();
        return EXIT_FAILURE ;
    }

    /* For each pair of <start>-<finish> */
    for (i = 1; i < argc; i++) {
        /* Parse the <x>-<y> from argv, storing how many elements we parsed. */
        res = sscanf(argv[i], "%zu-%zu", &first, &last);
        /* we expect at least one value, so error out if we don't have one. */
        if (res < 1) {
            putchar('\n');
            usage();
            fflush(stdout);
            free(buf);
            return EXIT_FAILURE ;
        }
        /* We have something like 2-, so we go till the last line. */
        if (res == 1) {
            last = SIZE_MAX;
        }
        /* Main brains of hail: Grab line and print it if it's in the range. */
        while (lineno < last) {
            if (getline(&buf, &len, fp) < 1) {
                /* EOF or error */
                break;
            }
            if (++lineno >= first) {
                fputs(buf, stdout);
            }
        }
    }
    /* Clean up and exit nicely */
    fflush(stdout);
    free(buf);
    return EXIT_SUCCESS ;
}
