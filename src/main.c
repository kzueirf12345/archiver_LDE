#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "streams/streams.h"
#include "zipping/zipping.h"
#include "utils/utils.h"

int main()
{
    FILE* stream_in = NULL, *stream_out = NULL;

    if (open_streams(&stream_in, &stream_out) == FAILURE)
    {
        fprintf(stderr, "OPEN FAILURE\n");
        return -1;
    }

    if (zipping(stream_in, stream_out) == FAILURE)
    {
        fprintf(stderr, "ZIPPING FAILURE\n");
        return -1;
    }

    if (close_streams(stream_in, stream_out) == FAILURE)
    {
        fprintf(stderr, "CLOSE FAILURE\n");
        return -1;
    }

    return 0;
}