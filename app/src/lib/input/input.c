#include <stdio.h>

void read_line(char *str) {
    char c;
    while ((c = getchar()) != '\n') {
        *str++ = c;
    }
    *str = 0;
}
