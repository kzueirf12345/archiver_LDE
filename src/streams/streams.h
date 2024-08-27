#ifndef SRC_OPEN_H
#define SRC_OPEN_H

#include <stdio.h>

#include "../utils/utils.h"


enum ErrorCode open_streams(FILE** const stream_in, FILE** const stream_out);

enum ErrorCode close_streams(FILE* stream_in, FILE* stream_out);

#endif /* SRC_OPEN_H */