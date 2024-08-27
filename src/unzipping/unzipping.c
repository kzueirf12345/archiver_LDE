#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>

#include "unzipping.h"

enum UnzippingState
{
    START,
    OPEN_BRAKET,
    SYMBOL_COUNT,
    CLOSE_BRAKET,
    SYMBOL
};

enum ErrorCode unzipping(FILE* stream_in, FILE* stream_out)
{
    assert(stream_in);
    assert(stream_out);


#define MAX_SYMBOL_COUNT_LEN 10

    size_t count_symbol_size = 0;
    char count_symbol_buf[MAX_SYMBOL_COUNT_LEN] = {};
    enum UnzippingState unzipping_state = START;
    char prev_symbol = EOF;
    char cur_symbol = (char)fgetc(stream_in);

    while (!feof(stream_in) && !ferror(stream_in))
    {
        switch (unzipping_state)
        {
        case START:
        {
            if (cur_symbol != '(')
                return INCORRECT;

            unzipping_state = OPEN_BRAKET;
            break;
        }

        case OPEN_BRAKET:
        {
            if (!isdigit(cur_symbol))
                return INCORRECT;

            unzipping_state = SYMBOL_COUNT;
            break;
        }

        case SYMBOL_COUNT:
        {
            if (cur_symbol == ')')
                unzipping_state = CLOSE_BRAKET;
            else if (!isdigit(cur_symbol))
                return INCORRECT;

            if (count_symbol_size > MAX_SYMBOL_COUNT_LEN)
                return INCORRECT;

            count_symbol_buf[count_symbol_size++] = prev_symbol;

            break;
        }

        case CLOSE_BRAKET:
        {
            if (cur_symbol != '(')
                return INCORRECT;

            unzipping_state = SYMBOL;

            memset(count_symbol_buf, 0, count_symbol_size);
            count_symbol_size = 0;

            break;
        }

        case SYMBOL:
        {
            unzipping_state = OPEN_BRAKET;
            
            char symbol = prev_symbol;

            size_t count_symbol = atol(count_symbol_buf);
            if (count_symbol == 0)
                return FAILURE;
            
            for (size_t i = 0; i < count_symbol; ++i)
            {
                if (fprintf(stream_out, "%c", symbol) <= 0)
                    return FAILURE;
            }
            break;
        }
        
        default:
            assert(!"Unknown error");
            break;
        }

        prev_symbol = cur_symbol;
        cur_symbol = (char)fgetc(stream_in);
    }
}