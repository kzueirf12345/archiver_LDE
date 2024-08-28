#include <assert.h>
#include <string.h>

#include "streams.h"

enum ErrorCode open_streams(FILE** const stream_in, FILE** const stream_out)
{
    assert(stream_in);
    assert(stream_out);


    printf("Enter the input file name: ");

#define MAX_FILENAME_LEN 256

    char filename_in[MAX_FILENAME_LEN] = {};
    if (scanf("%s", filename_in) != 1)
        return FAILURE;
    
    if (!(*stream_in = fopen(filename_in, "rb")))
        return FAILURE;


#define KWORD_NOT_OUTPUT_NAME "__NOT__"

    printf("Enter the output file name or "
           KWORD_NOT_OUTPUT_NAME
           " if you want create new file with input filename: ");

    char filename_out[MAX_FILENAME_LEN] = {};
    if (scanf("%s", filename_out) != 1)
        return FAILURE;

    if (!(*stream_out = fopen(!strcmp(filename_out, KWORD_NOT_OUTPUT_NAME)
                              ? strcat(filename_in, ".bin")
                              : filename_out, "wb")))
        return FAILURE;
    

    return SUCCESS;
}

enum ErrorCode close_streams(FILE** const stream_in, FILE** const stream_out)
{
    if (*stream_in && fclose(*stream_in))
        return FAILURE;
    *stream_in = NULL;
    
    if (*stream_out && fclose(*stream_out))
        return FAILURE;
    *stream_out = NULL;
    
    return SUCCESS;
}