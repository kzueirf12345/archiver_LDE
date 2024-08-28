#ifndef SRC_UNZIPPING_H
#define SRC_UNZIPPING_H

#include <stdio.h>

#include "../utils/utils.h"

enum ErrorCode unzipping2(FILE* stream_in, FILE* stream_out);

enum ErrorCode unzipping(FILE* stream_in, FILE* stream_out);


#endif /* SRC_UNZIPPING_H */