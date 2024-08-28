#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "streams/streams.h"
#include "zipping/zipping.h"
#include "unzipping/unzipping.h"
#include "utils/utils.h"

// #define ZIP

//TODO - rename project

int main()
{
    FILE* stream_in = NULL, *stream_out = NULL;

    // TODO - change mode

    if (open_streams(&stream_in, &stream_out) == FAILURE)
    {
        fprintf(stderr, "OPEN FAILURE\n");
        return -1;
    }

#ifdef ZIP

    if (zipping(stream_in, stream_out) == FAILURE)
    {
        fprintf(stderr, "ZIPPING FAILURE\n");
        return -1;
    }

#else /* ZIP */

    enum ErrorCode unzipping_code = unzipping(stream_in, stream_out);
    if (unzipping_code == FAILURE)
    {
        fprintf(stderr, "ZIPPING FAILURE\n");
        return -1;
    }
    if (unzipping_code == INCORRECT)
    {
        fprintf(stderr, "File for unzip is INCORRECT\n");
        return -1;
    }

#endif /* ZIP */

    if (close_streams(&stream_in, &stream_out) == FAILURE)
    {
        fprintf(stderr, "CLOSE FAILURE\n");
        return -1;
    }

    return 0;
}