/*
 * Copyright 2015 Kevin Murray
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        fprintf(stderr, "Usage: %s <first>-<last> [<first>-<last ...]\n",   \
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
        return(EXIT_FAILURE);
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
            return(EXIT_FAILURE);
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
            lineno++;
            if (lineno >= first) {
                fputs(buf, stdout);
            }
        }
    }
    /* Clean up and exit nicely */
    fflush(stdout);
    free(buf);
    return(EXIT_SUCCESS);
}
