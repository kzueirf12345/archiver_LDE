#ifndef SRC_ZIPPING_H
#define SRC_ZIPPING_H

#include <stdio.h>

#include "../utils/utils.h"

enum ErrorCode zipping2_achtung(FILE* stream_in, FILE* stream_out);

enum ErrorCode zipping(FILE* stream_in, FILE* stream_out);


#endif /* SRC_ZIPPING_H */