#include "zipping.h"

#include <assert.h>
#include <string.h>

enum ErrorCode zipping2(FILE* stream_in, FILE* stream_out)
{
    assert(stream_in);
    assert(stream_out);


    char prev_symbol = (char)fgetc(stream_in);
    char cur_symbol = EOF;
    unsigned symbol_count = 1;
    while (!feof(stream_in) && !ferror(stream_in))
    {
        cur_symbol = (char)fgetc(stream_in);
        if (cur_symbol != prev_symbol)
        {
            if (fprintf(stream_out, "(%u)%c", symbol_count, prev_symbol) <= 0)
                return ERROR_FAILURE;

            symbol_count = 1;
        }
        else
        {
            ++symbol_count;
        }
        prev_symbol = cur_symbol;
    }
    return ferror(stream_in) ? ERROR_FAILURE : ERROR_SUCCESS;
}

enum ErrorCode zipping(FILE* stream_in, FILE* stream_out)
{
    assert(stream_in);
    assert(stream_out);


    char prev_symbol = (char)fgetc(stream_in);
    char cur_symbol = EOF;
    unsigned char symbol_count = 1;
    while (!feof(stream_in) && !ferror(stream_in))
    {
        cur_symbol = (char)fgetc(stream_in);
        if (cur_symbol != prev_symbol)
        {
            if (fprintf(stream_out, "%c%c", symbol_count, prev_symbol) <= 0)
                return ERROR_FAILURE;

            symbol_count = 1;
        }
        else
        {
            if (symbol_count == 255)
                return ERROR_FAILURE;
            ++symbol_count;
        }
        prev_symbol = cur_symbol;
    }
    return ferror(stream_in) ? ERROR_FAILURE : ERROR_SUCCESS;
}
