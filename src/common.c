#include <syslog.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void * xmalloc(size_t size) {
    void *alloc = malloc (size);
    if (alloc == 0) {
        syslog (LOG_ERR, "out of memory (malloc)");
        exit (EXIT_FAILURE);
    }
    return alloc;
}
