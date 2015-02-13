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

#define usage() \
        printf("Usage: %s <first>-<last> [<first>-<last ...]\n", argv[0])
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

    if (argc < 2) {
        usage();
        return(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i++) {
        res = sscanf(argv[i], "%zu-%zu", &first, &last);
        if (res < 1) {
            /* we expect at least one value */
            putchar('\n');
            usage();
            break;
        }
        if (res == 1) {
            last = SIZE_MAX;
        }
        while (lineno < last) {
            if (getline(&buf, &len, fp) < 1) {
                /* EOF or error */
                break;
            }
            lineno++;
            if (lineno >= first) {
                fputs(buf, stdout);
            }
        }
    }
    fflush(stdout);
    free(buf);
    return(EXIT_SUCCESS);
}
