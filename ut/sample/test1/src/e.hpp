#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define PUT_8_2(t, s, n) ((t) |=\
(((s) & 0xC000) >> ((n) + 0)) |\
(((s) & 0x3000) >> ((n) + 2)) |\
(((s) & 0x0C00) >> ((n) + 4)) |\
(((s) & 0x0300) >> ((n) + 6)))
